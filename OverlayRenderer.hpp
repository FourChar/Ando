#ifndef OVERLAY_RENDERER_HPP
#define OVERLAY_RENDERER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "OverlayEvents.hpp"

namespace ando {
	namespace overlay {
		class OverlayRenderer : public OverlayEvents {
		public:
			virtual bool initialize() = 0;

			virtual bool BeginFrame() = 0;
			virtual bool RenderFrame() = 0;
			virtual bool EndFrame() = 0;

			virtual LRESULT CALLBACK windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
		}; // OverlayRenderer
	} // overlay
} // ando

#endif // OVERLAY_RENDERER_HPP