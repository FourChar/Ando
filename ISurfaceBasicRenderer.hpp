#ifndef ISURFACE_BASIC_RENDERER
#define ISURFACE_BASIC_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include "Color.hpp"
#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceBasicRenderer {
			public:
				virtual void DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ISurfaceFont *font, const char *string) = 0;
				virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color) = 0;
				virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color) = 0;
				virtual void FillRectangle(float x, float y, float width, float height, ando::Color color) = 0;
			};
		}
	}
}

#endif // ISURFACE_RENDERER