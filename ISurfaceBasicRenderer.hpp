#ifndef ISURFACE_BASIC_RENDERER
#define ISURFACE_BASIC_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>

#include "Color.hpp"
#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceBasicRenderer {
			public:
				virtual void DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ISurfaceFont> font, const char *string) { };
				virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color) { };
				virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color) { };
				virtual void FillRectangle(float x, float y, float width, float height, ando::Color color) { };
			};
		}
	}
}

#endif // ISURFACE_RENDERER