#ifndef ISURFACE_RENDERER
#define ISURFACE_RENDERER

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
			class ISurfaceRenderer : public ISurfaceBasicRenderer {
			protected:
				std::vector<std::shared_ptr<ISurfaceFont>> fonts;
				ando::overlay::surface::queue::ISurfaceQueue renderQueue;

			public:
				ISurfaceRenderer();

				void waitForEmptyQueue() const;

			protected:
				std::shared_ptr<ISurfaceFont> getFont(const std::string name, const uint8_t size) const;
				std::shared_ptr<ISurfaceFont> addFont(const std::string name, const uint8_t size, const uint16_t weight, const bool italics);
				void releaseFonts();

				virtual bool FontInitializer(const ISurfaceFont *font) = 0;

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

#endif // ISURFACE_RENDERER