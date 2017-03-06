#include <chrono>
#include <thread>
#include <dwmapi.h>
#include <wingdi.h>

#include "Overlay.hpp"

namespace ando {
	namespace overlay {
		Overlay::Overlay() {
			this->getTarget().setHwnd(0);
		}

		Overlay::~Overlay() {
			this->onDestroy();

			if (this->getLocal().getHwnd())
				DestroyWindow(this->getLocal().getHwnd());
		}

		bool Overlay::RunFrame() {
			if (!this->initialized) {
				this->running = false;
				return false;
			}

			if (this->getTarget().getHwnd() != GetForegroundWindow())
				return false;

			if (!this->BeginFrame())
				return false;

			if (!this->RenderFrame())
				return false;

			return this->EndFrame();
		}

		bool Overlay::RenderFrame() {
			this->renderQueue.processQueue(this);
			return true;
		}

		void Overlay::onDestroy() {
			this->running = false;
		}

		LRESULT CALLBACK Overlay::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			switch (message) {
				case WM_CREATE: {
					printf("Creating Overlay window...\r\n");
					this->getLocal().setHwnd(hWnd);

					SetLayeredWindowAttributes(hWnd, (COLORREF)RGB(0, 0, 0), (BYTE)255, LWA_COLORKEY | LWA_ALPHA);

					MARGINS margin = { -1, -1, -1, -1 };
					DwmExtendFrameIntoClientArea(hWnd, &margin);

					printf("Initializing Overlay...\r\n");
					this->initialized = this->initialize();

					if (this->initialized)
						printf("Initialized Overlay...\r\n");
					else
						printf("Failed to initialize Overlay!\r\n");

					break;
				}
				case WM_DESTROY: {
					printf("Destroying Overlay...\r\n");
					this->onDestroy();

					PostQuitMessage(1);
					return 1;
				}
				case WM_PAINT: {
					printf("WM_PAINT\r\n");
					return 0;
				}
				case WM_KEYDOWN: {
					printf("WM_KEYDOWN\r\n");
					return 0;
				}
				case WM_ERASEBKGND: {
					printf("WM_ERASEBKGND\r\n");
					SendMessage(hWnd, WM_PAINT, NULL, NULL);
					return TRUE;
				}
			}

			return DefWindowProcA(hWnd, message, wParam, lParam);
		}

		bool Overlay::waitForWindow(std::string targetWindowName) {
			while (this->getTarget().getHwnd() == NULL) {
				this->getTarget().setHwnd(FindWindow(NULL, targetWindowName.c_str()));

				using namespace std::chrono_literals;
				std::this_thread::sleep_for(2s);
			}

			this->getTarget().setWindowTitle(targetWindowName);
			this->alignToTarget();

			return true;
		}

		bool Overlay::createWindow() {
			printf("Creating window class...\r\n");
			WNDCLASSEX wcex;

			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = &Overlay::WindowProcessor;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = sizeof(Overlay*);
			wcex.hInstance = (HINSTANCE)GetWindowLong(this->getLocal().getHwnd(), GWL_HINSTANCE);
			wcex.hCursor = LoadCursor(0, IDC_ARROW);
			wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
			wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
			wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
			wcex.lpszMenuName = "ando::Overlay";
			wcex.lpszClassName = "ando::Overlay";

			printf("Registering window...\r\n");
			if (!RegisterClassEx(&wcex))
				return false;

			this->getLocal().setWindowTitle(wcex.lpszMenuName);

			printf("Creating Window...\r\n");
			HWND mainHandle = CreateWindowEx(
								WS_EX_TOPMOST | WS_EX_COMPOSITED | WS_EX_TRANSPARENT | WS_EX_LAYERED,
								wcex.lpszMenuName, wcex.lpszClassName, 
								WS_POPUP, 
								CW_USEDEFAULT, CW_USEDEFAULT,
								this->getTarget().getWidth(),
								this->getTarget().getHeight(),
								0, 0, 0, 
								static_cast<LPVOID>(this));
			if(!mainHandle)
				return false;

			this->getLocal().setHwnd(mainHandle);
			this->getLocal().setX(this->getTarget().getX());
			this->getLocal().setY(this->getTarget().getY());
			this->getLocal().setWidth(this->getTarget().getWidth());
			this->getLocal().setHeight(this->getTarget().getHeight());

			ShowWindow(mainHandle, SW_SHOWDEFAULT);

			if (!UpdateWindow(mainHandle))
				return false;

			if (!MoveWindow(mainHandle, this->getLocal().getX(), this->getLocal().getY(), this->getLocal().getWidth(), this->getLocal().getHeight(), TRUE))
				return false;

			SetForegroundWindow(this->getTarget().getHwnd());

			return true;
		}

		void Overlay::destroyWindow() {
			this->onDestroy();
			DestroyWindow(this->getLocal().getHwnd());
		}

		void Overlay::run() {
			printf("Running Overlay...\r\n");

			this->running = true;

			MSG message;
			uint8_t frameCounter = 0;

			while(this->running) {
				if(PeekMessage(&message, this->getLocal().getHwnd(), 0, 0, PM_REMOVE)) {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
				else {
					if (frameCounter++ > 254) {
						frameCounter = 0;

						if (!FindWindowA(NULL, this->getTarget().getWindowTitle().c_str())) {
							this->running = false;
							break;
						}
					}

					this->RunFrame();
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}

			this->destroyWindow();
		}

		void Overlay::alignToTarget() {
			printf("Aligning Overlay to Target...\r\n");

			RECT WindowSize;
			ZeroMemory(&WindowSize, sizeof(RECT));

			if (!GetWindowRect(this->getTarget().getHwnd(), &WindowSize))
				return;

			DWORD dwLong = GetWindowLong(this->getTarget().getHwnd(), GWL_STYLE);

			if (dwLong & WS_BORDER) {
				int x = GetSystemMetrics(SM_CXBORDER);
				int y = GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION);

				WindowSize.left += x;
				WindowSize.top += y;
				WindowSize.right -= x;
				WindowSize.bottom -= GetSystemMetrics(SM_CYBORDER);
			}

			this->getTarget().setX(WindowSize.left);
			this->getTarget().setY(WindowSize.top);
			this->getTarget().setWidth(WindowSize.right - WindowSize.left);
			this->getTarget().setHeight(WindowSize.bottom - WindowSize.top);

			this->getLocal().setX(this->getTarget().getX());
			this->getLocal().setY(this->getTarget().getY());
			this->getLocal().setWidth(this->getTarget().getWidth());
			this->getLocal().setHeight(this->getTarget().getHeight());

			if(this->localInstance.getHwnd())
				MoveWindow(this->getLocal().getHwnd(), this->getLocal().getX(), this->getLocal().getY(), this->getLocal().getWidth(), this->getLocal().getHeight(), TRUE);
		}

		ando::OverlayInstance &Overlay::getTarget() {
			return this->targetInstance;
		}
		ando::OverlayInstance &Overlay::getLocal() {
			return this->localInstance;
		}

		bool Overlay::isInitialized() const {
			return this->initialized;
		}

		bool Overlay::isRunning() const {
			return this->running;
		}

		bool Overlay::canRunExternaly() const {
			this->waitForEmptyQueue();
			return this->isRunning();
		}
	}
};