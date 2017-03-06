#ifndef GDI_OVERLAY_HPP
#define GDI_OVERLAY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "Overlay.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			class GDIOverlay : public Overlay {
			public:
				GDIOverlay();

				virtual bool initialize();

				virtual bool BeginFrame();
				virtual bool RenderFrame();
				virtual bool EndFrame();

				virtual void onDestroy();
				virtual void onReset();
				virtual void onRelease();
				virtual void onResize();

				virtual bool FontInitializer(const ando::overlay::surface::ISurfaceFont *font);

				virtual void DrawRawString(float x, float y, float scale, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *format);
				virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color);
				virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color);
				virtual void FillRectangle(float x, float y, float width, float height, ando::Color color);
			};
		}
	}
}

#endif // GDI_OVERLAY_HPP