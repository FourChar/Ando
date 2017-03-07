#ifndef ISURFACE_ADVANCED_RENDERER
#define ISURFACE_ADVANCED_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include "ISurfaceBasicRenderer.hpp"
#include "ISurfaceQueue.hpp"
#include "ISurfaceFont.hpp"
#include "Color.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceAdvancedRenderer : public ISurfaceBasicRenderer {
			public:
				virtual void DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, std::string fontName, const char * format, ...);
				virtual void DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, uint8_t size, ando::Color color, std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, ando::Color color, ando::Color outlineColor, std::string fontName, const char * format, ...);
				virtual void DrawOutlinedString(float x, float y, ando::Color color, std::string fontName, const char *format, ...);

				virtual void DrawString(float x, float y, ando::Color color, std::string fontName, const char *format, ...);
				virtual void DrawString(float x, float y, uint8_t size, bool centered, ando::Color color, std::string fontName, const char *format, ...);

			public:
				virtual void DrawOutlinedLine(float x1, float y1, float x2, float y2, ando::Color color, ando::Color outlineColor = ando::colors::black);

			public:
				virtual void DrawOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor = ando::colors::black);

				virtual void FillOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor = ando::colors::black);
			};
		}
	}
}

#endif // ISURFACE_ADVANCED_RENDERER