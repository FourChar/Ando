#ifndef ISURFACE_QUEUED_RENDERER
#define ISURFACE_QUEUED_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include "ISurfaceBasicRenderer.hpp"
#include "ISurfaceFontRenderer.hpp"
#include "ISurfaceQueue.hpp"
#include "ISurfaceFont.hpp"
#include "Color.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceQueuedRenderer : public ISurfaceBasicRenderer {
			protected:
				ando::overlay::surface::ISurfaceFontRenderer *renderer;
				std::shared_ptr<ando::overlay::surface::queue::ISurfaceQueue> renderQueue;

			public:
				ISurfaceQueuedRenderer(ando::overlay::surface::ISurfaceFontRenderer *renderer);

				std::shared_ptr<ando::overlay::surface::queue::ISurfaceQueue> getRenderQueue();

			public:
				virtual void DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ISurfaceFont> font, const char *string);
				virtual void DrawLine(float x1, float y1, float x2, float y2, ando::Color color);
				virtual void DrawRectangle(float x, float y, float width, float height, ando::Color color);
				virtual void FillRectangle(float x, float y, float width, float height, ando::Color color);

				virtual void DrawString(float x, float y, ando::Color color, ::std::string fontName, const char *format, ...);
				virtual void DrawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...);

				virtual void DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char * format, ...);
				virtual void DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, uint8_t size, ando::Color color, ::std::string fontName, const char *format, ...);
				virtual void DrawOutlinedString(float x, float y, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char * format, ...);
				virtual void DrawOutlinedString(float x, float y, ando::Color color, ::std::string fontName, const char *format, ...);

				virtual void DrawOutlinedLine(float x1, float y1, float x2, float y2, ando::Color color, ando::Color outlineColor = ando::colors::black);

				virtual void DrawOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor = ando::colors::black);

				virtual void FillOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor = ando::colors::black);

				virtual void DrawProgressBar(float x, float y, float width, float height, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible);
				virtual void DrawOutlinedProgressBar(float x, float y, float width, float height, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible, ando::Color outlineColor = ando::colors::black);
			};
		}
	}
}

#endif // ISURFACE_QUEUED_RENDERER