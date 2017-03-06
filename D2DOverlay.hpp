#ifndef D2D_OVERLAY_HPP
#define D2D_OVERLAY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <vector>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite_2.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Dwrite.lib")

#include "Overlay.hpp"
#include "D2DColor.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			class D2DOverlay : public Overlay {
			private:
				ID2D1Factory *factory;
				ID2D1HwndRenderTarget *renderTarget;
				IDWriteFactory *writeFactory;

				std::vector<direct2d::D2DColor*> colors;

			protected:
				std::shared_ptr<ID2D1SolidColorBrush *> toD2DColor(ando::Color color);

			public:
				IDWriteFactory *getWriteFactory();

			public:
				D2DOverlay();

				virtual bool initialize();

				virtual bool BeginFrame();
				virtual bool EndFrame();

				virtual void onDestroy();
				virtual void onReset();
				virtual void onRelease();
				virtual void onResize();

				virtual bool FontInitializer(const ando::overlay::surface::ISurfaceFont *font);

				virtual void DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *string);
				virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color);
				virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color);
				virtual void FillRectangle(float x, float y, float width, float height, ando::Color color);
			};
		}
	}
}

#endif