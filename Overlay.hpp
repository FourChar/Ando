#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <windows.h>

#include "ISurfaceRenderer.hpp"
#include "OverlayRenderer.hpp"
#include "OverlayInstance.hpp"
#include "ISurfaceFont.hpp"

#pragma comment(lib, "dwmapi.lib")

namespace ando {
	namespace overlay {
		class Overlay : public ando::OverlayRenderer, public ando::overlay::surface::ISurfaceRenderer {
		public:
			Overlay();
			~Overlay();

			virtual LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			bool waitForWindow(std::string targetWindowName);
			bool createWindow();

			void destroyWindow();

			void runThread();
			void run();

			void alignToTarget();

			bool RunFrame();

			virtual bool RenderFrame();

			virtual void onDestroy();

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

			bool isInitialized() const;
			bool isRunning() const;
			bool canRunExternaly() const;

		protected:
			ando::OverlayInstance targetInstance;
			ando::OverlayInstance localInstance;
			
		protected:
			bool initialized;
			bool running;
		};
	}
}

#endif // OVERLAY_HPP