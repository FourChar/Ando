#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#define ANDO_OVERLAY_VERSION				"1.9.8.5"

#include <Windows.h>

#include "ISurfaceQueuedRenderer.hpp"
#include "ISurfaceFontRenderer.hpp"
#include "ISurfaceFont.hpp"
#include "OverlayRenderer.hpp"
#include "OverlayInstance.hpp"
#include "CProcessHandler.hpp"
#include "IBasicLogger.hpp"
#include "ILogger.hpp"
#include "ISafeLogger.hpp"

#pragma comment(lib, "dwmapi.lib")

namespace ando {
	namespace overlay {
		class Overlay : public ando::overlay::OverlayRenderer, public ando::overlay::surface::ISurfaceFontRenderer {
		public:
			Overlay();
			Overlay(::std::shared_ptr<ando::logger::ILogger> logger);

			~Overlay();

		public:
			static __inline ::std::string getVersion() {
				return ANDO_OVERLAY_VERSION;
			}

			bool bindToWindow(::std::string targetWindowName);

			std::shared_ptr<std::thread> runThreaded();
			void render(::std::function<void(ando::overlay::surface::ISurfaceQueuedRenderer &renderer)> f);

		protected:
			virtual LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			bool waitForWindow(::std::string targetWindowName);
			bool createWindow();

			void destroyWindow();
			void alignToTarget();

			bool RunFrame();

			virtual bool RenderFrame();
			virtual void onDestroy();

			void run();
			void runWindow();

			static LRESULT CALLBACK WindowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
				if(message == WM_NCCREATE) {
					CREATESTRUCT *create = reinterpret_cast<CREATESTRUCT*>(lParam);
					SetWindowLongPtrW(hWnd, 0, reinterpret_cast<LONG_PTR>(create->lpCreateParams));
				}

				auto overlay = reinterpret_cast<ando::overlay::Overlay *>(GetWindowLongPtrW(hWnd, 0));

				if(overlay) {
					if(message == WM_NCDESTROY) {
						overlay->onDestroy();
					}

					return overlay->windowProc(hWnd, message, wParam, lParam);
				}
				
				return DefWindowProcA(hWnd, message, wParam, lParam);
			}

		public:
			::std::shared_ptr<ando::overlay::OverlayInstance> getTarget();
			::std::shared_ptr<ando::overlay::OverlayInstance> getLocal();

		public:
			::std::shared_ptr<::ando::memory::CProcessHandler> getProcessHandler();
			::std::shared_ptr<::ando::overlay::surface::ISurfaceQueuedRenderer> getQueuedRenderer();

			template <typename T>
			::std::shared_ptr<T> makeProcessInstance() {
				return ::std::make_shared<T>(this->logger->getLogger(), this->getProcessHandler(), this->getTarget());
			}

		protected:
			bool isInitialized() const;
			bool isRunning() const;

			void setRunning(bool running);

			void waitForEmptyQueue();
			bool canRunExternaly();

		protected:
			::std::shared_ptr<ando::overlay::OverlayInstance> targetInstance;
			::std::shared_ptr<ando::overlay::OverlayInstance> localInstance;
			
		private:
			bool initialized;
			bool running;
			
			DWORD mainThreadId;

		protected:
			::std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> queuedRenderer;
			::std::shared_ptr<::std::thread> renderThread;
			::std::unique_ptr<::std::mutex> renderMutex;
			::std::shared_ptr<ando::logger::ISafeLogger> logger;
		}; // class Overlay
	} // namespace overlay
} // namespace ando

#endif // OVERLAY_HPP