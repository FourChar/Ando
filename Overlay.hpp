#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <windows.h>

#include "ISurfaceQueuedRenderer.hpp"
#include "ISurfaceFontRenderer.hpp"
#include "ISurfaceFont.hpp"
#include "OverlayRenderer.hpp"
#include "OverlayInstance.hpp"

#pragma comment(lib, "dwmapi.lib")

namespace ando {
	namespace overlay {
		class Overlay : public ando::overlay::OverlayRenderer, public ando::overlay::surface::ISurfaceFontRenderer {
		public:
			Overlay();
			~Overlay();

			bool waitForWindow(std::string targetWindowName);
			bool createWindow();

			std::shared_ptr<std::thread> runThreaded();
			void runExternal(std::function<void(std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> renderer)> f);

			bool canRunExternaly();

		protected:
			virtual LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void destroyWindow();
			void alignToTarget();

			bool RunFrame();

			virtual bool RenderFrame();
			virtual void onDestroy();

			void run();

			static LRESULT CALLBACK WindowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
				if(message == WM_NCCREATE) {
					CREATESTRUCT *create = reinterpret_cast<CREATESTRUCT*>(lParam);
					SetWindowLongPtrW(hWnd, 0, reinterpret_cast<LONG_PTR>(create->lpCreateParams));
				}

				Overlay *overlay = reinterpret_cast<Overlay*>(GetWindowLongPtrW(hWnd, 0));

				if(overlay) {
					if(message == WM_NCDESTROY) {
						overlay->onDestroy();
					}

					return overlay->windowProc(hWnd, message, wParam, lParam);
				}
				
				return DefWindowProcA(hWnd, message, wParam, lParam);
			}

		public:
			ando::OverlayInstance &getTarget();
			ando::OverlayInstance &getLocal();

		protected:
			bool isInitialized() const;
			bool isRunning() const;

			void setRunning(bool running);

			void waitForEmptyQueue();

		protected:
			ando::OverlayInstance targetInstance;
			ando::OverlayInstance localInstance;
			
		private:
			bool initialized;
			bool running;

		protected:
			std::shared_ptr<ando::overlay::surface::ISurfaceQueuedRenderer> queuedRenderer;
			std::shared_ptr<std::thread> renderThread;
			std::unique_ptr<std::mutex> renderMutex;
		}; // class Overlay
	} // namespace overlay
} // namespace ando

#endif // OVERLAY_HPP