#ifndef ISURFACE_ADVANCED_RENDERER
#define ISURFACE_ADVANCED_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include <cstdarg>

#define FORMAT_STRING(s)		char buffer[s] = {0}; { va_list args; va_start(args, format); vsprintf_s(buffer, format, args); va_end(args); }

#include "ISurfaceBasicRenderer.hpp"
#include "ISurfaceQueue.hpp"
#include "ISurfaceFont.hpp"
#include "Vector2.hpp"
#include "Color.hpp"
#include "Rect.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceAdvancedRenderer : public ISurfaceBasicRenderer {
			public:
				virtual void DrawRawString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ISurfaceFont> font, const char *string);

				virtual void DrawString(float x, float y, ando::Color color, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawString(ando::math::Vector2<float> coordinates, ando::Color color, ::std::string fontName, const char *format, ...);
				virtual void DrawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...);

				virtual void DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, uint8_t size, ando::Color color, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, ando::Color color, ::std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, ando::Color color, ::std::string fontName, const char *format, ...) = 0;
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, ando::Color color, ::std::string fontName, const char *format, ...);

			public:
				virtual void DrawLine(ando::math::Vector2<float> startCoordinates, ando::math::Vector2<float> endCoordinates, ando::Color color);

				virtual void DrawOutlinedLine(float x1, float y1, float x2, float y2, ando::Color color, ando::Color outlineColor = ando::colors::black) = 0;
				virtual void DrawOutlinedLine(ando::math::Vector2<float> startCoordinates, ando::math::Vector2<float> endCoordinates, ando::Color color, ando::Color outlineColor = ando::colors::black);

			public:
				virtual void DrawRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color);
				virtual void DrawRectangle(ando::math::Rect<float> rect, ando::Color color);

				virtual void DrawOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor = ando::colors::black) = 0;
				virtual void DrawOutlinedRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color, ando::Color outlineColor = ando::colors::black);
				virtual void DrawOutlinedRectangle(ando::math::Rect<float> rect, ando::Color color, ando::Color outlineColor = ando::colors::black);

				virtual void FillRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color);
				virtual void FillRectangle(ando::math::Rect<float> rect, ando::Color color);

				virtual void FillOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor = ando::colors::black) = 0;
				virtual void FillOutlinedRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color, ando::Color outlineColor = ando::colors::black);
				virtual void FillOutlinedRectangle(ando::math::Rect<float> rect, ando::Color color, ando::Color outlineColor = ando::colors::black);

			public:
				virtual void DrawProgressBar(float x, float y, float width, float height, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible) = 0;
				virtual void DrawProgressBar(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible);
				virtual void DrawProgressBar(ando::math::Rect<float> rect, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible);

				virtual void DrawOutlinedProgressBar(float x, float y, float width, float height, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible, ando::Color outlineColor = ando::colors::black) = 0;
				virtual void DrawOutlinedProgressBar(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible, ando::Color outlineColor = ando::colors::black);
				virtual void DrawOutlinedProgressBar(ando::math::Rect<float> rect, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible, ando::Color outlineColor = ando::colors::black);
			};
		}
	}
}

#endif // ISURFACE_ADVANCED_RENDERER