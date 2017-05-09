#include <chrono>
#include <thread>
#include <dwmapi.h>
#include <wingdi.h>

#include "Overlay.hpp"

#include "ELogLevel.hpp"

using ando::logger::ELogLevel;

// TODO: Create seperate thread for everything window related
namespace ando {
	namespace overlay {
		Overlay::Overlay() {
			this->targetInstance = ::std::make_shared<ando::overlay::OverlayInstance>();
			this->localInstance = ::std::make_shared<ando::overlay::OverlayInstance>();
			this->queuedRenderer = ::std::make_shared<ando::overlay::surface::ISurfaceQueuedRenderer>(this);

			this->getTarget()->setHwnd(0);
			this->renderThread = nullptr;
			this->logger = ::std::make_shared<::ando::logger::ISafeLogger>();
		}
		Overlay::Overlay(::std::shared_ptr<ando::logger::ILogger> logger) {
			this->targetInstance = ::std::make_shared<ando::overlay::OverlayInstance>();
			this->localInstance = ::std::make_shared<ando::overlay::OverlayInstance>();
			this->queuedRenderer = ::std::make_shared<ando::overlay::surface::ISurfaceQueuedRenderer>(this);

			this->getTarget()->setHwnd(0);
			this->renderThread = nullptr;
			this->logger = ::std::make_shared<::ando::logger::ISafeLogger>(logger);
		}

		Overlay::~Overlay() {
			this->destroyWindow();

			if (this->renderThread)
				this->renderThread->join();
		}

		bool Overlay::bindToWindow(::std::string targetWindowName) {
			if (!this->waitForWindow(targetWindowName))
				return false;

			return this->createWindow();
		}

		std::shared_ptr<std::thread> Overlay::runThreaded() {
			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::runThreaded} Starting renderThread...");

			this->renderMutex = ::std::make_unique<std::mutex>();
			return (this->renderThread = ::std::make_shared<std::thread>(::std::bind(&ando::overlay::Overlay::run, this)));
		}

		void Overlay::render(::std::function<void(ando::overlay::surface::ISurfaceQueuedRenderer &renderer)> f) {
			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::render} Starting external renderer...");

			while (this->canRunExternaly()) {
				f(*this->queuedRenderer.get());
			}
		}

		LRESULT CALLBACK Overlay::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message) {
				case WM_CREATE: {
					this->logger->log(ELogLevel::LOG_INFO, "{Overlay::windowProc} Creating Overlay window...");
					this->getLocal()->setHwnd(hWnd);

					SetLayeredWindowAttributes(hWnd, (COLORREF)RGB(0, 0, 0), (BYTE)255, LWA_COLORKEY | LWA_ALPHA);

					MARGINS margin = { -1, -1, -1, -1 };
					DwmExtendFrameIntoClientArea(hWnd, &margin);

					this->logger->log(ELogLevel::LOG_INFO, "{Overlay::windowProc} Initializing Overlay...");
					this->initialized = this->initialize();

					if (this->isInitialized()) {
						this->logger->log(ELogLevel::LOG_INFO, "{Overlay::windowProc} Initialized Overlay...");
					}
					else {
						this->logger->log(ELogLevel::LOG_ERROR, "{Overlay::windowProc} Failed to initialize Overlay!");
					}

					break;
				}
				case WM_DESTROY: {
					this->logger->log(ELogLevel::LOG_INFO, "{Overlay::windowProc} Destroying Overlay...");
					this->onDestroy();

					PostQuitMessage(1);
					return 1;
				}
				case WM_SIZE:
				case WM_MOVE: {
					if(this->isInitialized())
						this->onResize();

					break;
				}
				case WM_PAINT: {
					return 0;
				}
				case WM_KEYDOWN: {
					return 0;
				}
				case WM_ERASEBKGND: {
					SendMessageA(hWnd, WM_PAINT, NULL, NULL);
					return TRUE;
				}
			}

			return DefWindowProcA(hWnd, message, wParam, lParam);
		}

		bool Overlay::waitForWindow(::std::string targetWindowName) {
			this->logger->log(ELogLevel::LOG_INFO, "{Overlay::waitForWindow} Waiting for window \"%s\"...", targetWindowName.c_str());

			while (this->getTarget()->getHwnd() == NULL) {
				this->getTarget()->setHwnd(FindWindowA(NULL, targetWindowName.c_str()));

				std::this_thread::sleep_for(::std::chrono::seconds(2));
			}

			this->logger->log(ELogLevel::LOG_INFO, "{Overlay::waitForWindow} Found window! (HWND: 0x%.8X)", this->getTarget()->getHwnd());

			this->getTarget()->setWindowTitle(targetWindowName);
			this->alignToTarget();

			return true;
		}
		bool Overlay::createWindow() {
			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::createWindow} Creating window class...");

			WNDCLASSEX wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = &ando::overlay::Overlay::WindowProcessor;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = sizeof(ando::overlay::Overlay *);
			wcex.hInstance = (HINSTANCE)GetWindowLongPtrA(this->getLocal()->getHwnd(), GWLP_HINSTANCE);
			wcex.hCursor = LoadCursor(0, IDC_ARROW);
			wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
			wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
			wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
			wcex.lpszMenuName = "ando::Overlay";
			wcex.lpszClassName = "ando::Overlay";

			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::createWindow} Registering window...");
			if (!RegisterClassExA(&wcex)) {
				this->logger->log(ELogLevel::LOG_ERROR, "{Overlay::createWindow} Failed to register window!");
				return false;
			}

			this->getLocal()->setWindowTitle(wcex.lpszMenuName);

			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::createWindow} Creating window...");
			HWND mainHandle = CreateWindowExA(
				WS_EX_TOPMOST | WS_EX_COMPOSITED | WS_EX_TRANSPARENT | WS_EX_LAYERED,
				wcex.lpszMenuName, wcex.lpszClassName,
				WS_POPUP,
				CW_USEDEFAULT, CW_USEDEFAULT,
				this->getTarget()->getWidth(),
				this->getTarget()->getHeight(),
				0, 0, 0,
				static_cast<LPVOID>(this));

			if (!mainHandle) {
				this->logger->log(ELogLevel::LOG_ERROR, "{Overlay::createWindow} Failed to create window!");
				return false;
			}

			this->mainThreadId = GetCurrentThreadId();

			this->getLocal()->setHwnd(mainHandle);
			this->getLocal()->setX(this->getTarget()->getX());
			this->getLocal()->setY(this->getTarget()->getY());
			this->getLocal()->setWidth(this->getTarget()->getWidth());
			this->getLocal()->setHeight(this->getTarget()->getHeight());

			ShowWindow(mainHandle, SW_SHOWDEFAULT);

			if (!UpdateWindow(mainHandle)) {
				this->logger->log(ELogLevel::LOG_ERROR, "{Overlay::createWindow} Failed to update window!");
				return false;
			}

			if (!MoveWindow(mainHandle, this->getLocal()->getX(), this->getLocal()->getY(), this->getLocal()->getWidth(), this->getLocal()->getHeight(), TRUE)) {
				this->logger->log(ELogLevel::LOG_ERROR, "{Overlay::createWindow} Failed to move window!");
				return false;
			}

			SetForegroundWindow(this->getTarget()->getHwnd());

			return true;
		}

		void Overlay::destroyWindow() {
			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::destroyWindow} Destroying window...");

			this->running = false;

			if(this->getLocal()->getHwnd())
				DestroyWindow(this->getLocal()->getHwnd());
		}
		void Overlay::alignToTarget() {
			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Aligning overlay to target...");
			
			RECT windowSize;
			ZeroMemory(&windowSize, sizeof(RECT));

			if (!GetWindowRect(this->getTarget()->getHwnd(), &windowSize))
				return;

			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Found window RECT (%u, %u, %u, %u)", windowSize.left, windowSize.top, windowSize.right, windowSize.bottom);

			DWORD dwLong = GetWindowLongA(this->getTarget()->getHwnd(), GWL_STYLE);

			if (dwLong & WS_BORDER) {
				this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Adjusting for border...");

				int x = GetSystemMetrics(SM_CXBORDER);
				int y = GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION);

				windowSize.left += x;
				windowSize.top += y;
				windowSize.right -= x;
				windowSize.bottom -= GetSystemMetrics(SM_CYBORDER);
			}

			this->getTarget()->setX(windowSize.left);
			this->getTarget()->setY(windowSize.top);
			this->getTarget()->setWidth(windowSize.right - windowSize.left);
			this->getTarget()->setHeight(windowSize.bottom - windowSize.top);

			bool windowChanged = false;

			if ((this->getLocal()->getX() != this->getTarget()->getX()) && (this->getLocal()->getY() != this->getTarget()->getY())) {
				this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Window has moved");
				windowChanged = true;
			}
			if ((this->getLocal()->getWidth() != this->getTarget()->getWidth()) && (this->getLocal()->getHeight() != this->getTarget()->getHeight())) {
				this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Window has resized");
				windowChanged = true;

				this->onResize();
			}

			if (!windowChanged)
				return;

			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Setting Overlay instances (%u, %u, %u, %u)...", windowSize.left, windowSize.top, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);
			this->getLocal()->setX(this->getTarget()->getX());
			this->getLocal()->setY(this->getTarget()->getY());
			this->getLocal()->setWidth(this->getTarget()->getWidth());
			this->getLocal()->setHeight(this->getTarget()->getHeight());

			if (!this->localInstance->getHwnd())
				return;

			WINDOWPOS windowPosition;
			windowPosition.hwnd = this->getLocal()->getHwnd();
			windowPosition.hwndInsertAfter = HWND_TOPMOST;
			windowPosition.x = this->getLocal()->getX();
			windowPosition.y = this->getLocal()->getY();
			windowPosition.cx = this->getLocal()->getWidth();
			windowPosition.cy = this->getLocal()->getHeight();

			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::alignToTarget} Moving window...");
			
			PostThreadMessageA(this->mainThreadId, WM_WINDOWPOSCHANGING, NULL, (LPARAM)&windowPosition);
			PostThreadMessageA(this->mainThreadId, WM_WINDOWPOSCHANGED, NULL, (LPARAM)&windowPosition);
			PostThreadMessageA(this->mainThreadId, WM_MOVE, NULL, MAKELPARAM(windowPosition.x, windowPosition.y));
			PostThreadMessageA(this->mainThreadId, WM_SIZE, SIZE_RESTORED, MAKELPARAM(windowPosition.cx, windowPosition.cy));
			PostThreadMessageA(this->mainThreadId, WM_NCCALCSIZE, FALSE, (LPARAM)&windowSize);

			// TODO: Move window creation and run logic to single thread
			//PostThreadMessage(this->mainThreadId, WM_MOVE, )
			/*if (!MoveWindow(this->getLocal().getHwnd(), this->getLocal().getX(), this->getLocal().getY(), this->getLocal().getWidth(), this->getLocal().getHeight(), TRUE)) {
				ANDO_SAFE_LOG(ELogLevel::LOG_WARNING, "Failed to move window!");
			}*/
		}

		bool Overlay::RunFrame() {
			if (!this->initialized) {
				this->running = false;
				return false;
			}

			if (this->getTarget()->getHwnd() != GetForegroundWindow())
				return false;

			if (!this->BeginFrame())
				return false;

			if (!this->RenderFrame())
				return false;

			return this->EndFrame();
		}

		bool Overlay::RenderFrame() {
			this->queuedRenderer->getRenderQueue()->processQueue();
			return true;
		}
		void Overlay::onDestroy() {
			this->running = false;
		}

		void Overlay::run() {
			this->logger->log(ELogLevel::LOG_INFO, "{Overlay::run} Running Overlay...");

			this->running = true;

			MSG message;
			uint8_t frameCounter = 0;

			while(this->running) {
				while(PeekMessageA(&message, this->getLocal()->getHwnd(), 0, 0, PM_REMOVE)) {
					TranslateMessage(&message);
					DispatchMessageA(&message);
				}

				if (frameCounter++ >= 254) {
					frameCounter = 0;

					// Have to move all the window logic to it's own thread to be able to move the window from this thread
					//this->alignToTarget();

					if (!FindWindowA(NULL, this->getTarget()->getWindowTitle().c_str())) {
						this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::run} Window closed!");
						this->running = false;
						break;
					}
				}

				this->RunFrame();

				std::this_thread::sleep_for(::std::chrono::milliseconds(1));
			}

			this->destroyWindow();
			this->logger->log(ELogLevel::LOG_DEBUG, "{Overlay::run} Destroyed window!");
		}

		// TODO: *See TODO at the end of ::ando::overlay::Overlay::alignToTarget()*
		void Overlay::runWindow() {

		}

		std::shared_ptr<ando::overlay::OverlayInstance> Overlay::getTarget() {
			return this->targetInstance;
		}
		std::shared_ptr<ando::overlay::OverlayInstance> Overlay::getLocal() {
			return this->localInstance;
		}

		::std::shared_ptr<::ando::memory::CProcessHandler> Overlay::getProcessHandler() {
			static ::std::shared_ptr<::ando::memory::CProcessHandler> processHandler = nullptr;

			if (this->getTarget()->getHwnd() == NULL)
				return nullptr;

			if (processHandler == nullptr) {
				processHandler = ::std::make_shared<::ando::memory::CProcessHandler>(this->getTarget()->getHwnd());
			}

			return processHandler;
		}
		::std::shared_ptr<::ando::overlay::surface::ISurfaceQueuedRenderer> Overlay::getQueuedRenderer() {
			return this->queuedRenderer;
		}

		bool Overlay::isInitialized() const {
			return this->initialized;
		}
		bool Overlay::isRunning() const {
			if (this->renderMutex)
				this->renderMutex->lock();
			
			bool result = this->running;

			if (this->renderMutex)
				this->renderMutex->unlock();

			return result;
		}

		void Overlay::setRunning(bool running) {
			if (this->renderMutex)
				this->renderMutex->lock();

			this->running = running;

			if (this->renderMutex)
				this->renderMutex->unlock();
		}

		void Overlay::waitForEmptyQueue() {
			while (this->isRunning() && !this->queuedRenderer->getRenderQueue()->isQueueEmpty());
		}
		bool Overlay::canRunExternaly() {
			if (!this->isRunning())
				return false;

			this->waitForEmptyQueue();
			return true;
		}
	}
};