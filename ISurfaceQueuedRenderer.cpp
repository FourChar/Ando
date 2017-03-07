#include "ISurfaceQueuedRenderer.hpp"

#include <cstdarg>
#include <thread>

#define FORMAT_STRING(s)		char buffer[s] = {0}; { va_list args; va_start(args, format); vsprintf_s(buffer, format, args); va_end(args); }

namespace ando {
	namespace overlay {
		namespace surface {
			ISurfaceQueuedRenderer::ISurfaceQueuedRenderer(ando::overlay::surface::ISurfaceFontRenderer *renderer) {
				this->renderer = renderer;
				this->renderQueue = std::make_shared<ando::overlay::surface::queue::ISurfaceQueue>(renderer);
			}

			std::shared_ptr<ando::overlay::surface::queue::ISurfaceQueue> ISurfaceQueuedRenderer::getRenderQueue() {
				return this->renderQueue;
			}

			void ISurfaceQueuedRenderer::DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, std::shared_ptr<ISurfaceFont> font, const char *string) {
				this->renderQueue->DrawRawString(x, y, size, centered, color, font, string);
			}
			void ISurfaceQueuedRenderer::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
				this->renderQueue->DrawLine(x1, y1, x2, y2, color);
			}
			void ISurfaceQueuedRenderer::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
				this->renderQueue->DrawRectangle(x, y, width, height, color);
			}
			void ISurfaceQueuedRenderer::FillRectangle(float x, float y, float width, float height, ando::Color color) {
				this->renderQueue->FillRectangle(x, y, width, height, color);
			}

			void ISurfaceQueuedRenderer::DrawString(float x, float y, ando::Color color, std::string fontName, const char *format, ...) {
				std::shared_ptr<ISurfaceFont> font = this->renderer->getOrCreateFont(fontName, ISURFACE_TEXT_SIZE_DEFAULT);

				FORMAT_STRING(256);

				this->DrawRawString(x, y, ISURFACE_TEXT_SIZE_DEFAULT, false, color, font, buffer);
			}
			void ISurfaceQueuedRenderer::DrawString(float x, float y, uint8_t size, bool centered, ando::Color color, std::string fontName, const char *format, ...) {
				std::shared_ptr<ISurfaceFont> font = this->renderer->getOrCreateFont(fontName, size);

				FORMAT_STRING(256);

				this->DrawRawString(x, y, size, centered, color, font, buffer);
			}

			void ISurfaceQueuedRenderer::DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, std::string fontName, const char * format, ...) {
				std::shared_ptr<ISurfaceFont> font = this->renderer->getOrCreateFont(fontName, size);

				FORMAT_STRING(256);

				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->DrawRawString(x - 1, y - 1, size, centered, outlineColor, font, buffer);
				this->DrawRawString(x - 1, y + 1, size, centered, outlineColor, font, buffer);
				this->DrawRawString(x + 1, y - 1, size, centered, outlineColor, font, buffer);
				this->DrawRawString(x + 1, y + 1, size, centered, outlineColor, font, buffer);
				this->DrawRawString(x, y, size, centered, color, font, buffer);
			}
			void ISurfaceQueuedRenderer::DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, size, centered, color, ando::colors::black, fontName, buffer);
			}
			void ISurfaceQueuedRenderer::DrawOutlinedString(float x, float y, uint8_t size, ando::Color color, std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, size, ISURFACE_TEXT_CENTERED_DEFAULT, color, fontName, buffer);
			}
			void ISurfaceQueuedRenderer::DrawOutlinedString(float x, float y, ando::Color color, ando::Color outlineColor, std::string fontName, const char * format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, ISURFACE_TEXT_SIZE_DEFAULT, ISURFACE_TEXT_CENTERED_DEFAULT, color, outlineColor, fontName, buffer);
			}
			void ISurfaceQueuedRenderer::DrawOutlinedString(float x, float y, ando::Color color, std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, ISURFACE_TEXT_SIZE_DEFAULT, ISURFACE_TEXT_CENTERED_DEFAULT, color, ando::colors::black, fontName, buffer);
			}

			void ISurfaceQueuedRenderer::DrawOutlinedLine(float x1, float y1, float x2, float y2, ando::Color color, ando::Color outlineColor) {
				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->DrawLine(x1 - 1, y1 - 1, x2 - 1, y2 - 1, outlineColor);
				this->DrawLine(x1, y1, x2, y2, color);
			}

			void ISurfaceQueuedRenderer::DrawOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor) {
				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->DrawRectangle(x + 1, y + 1, width - 2, height - 2, outlineColor);
				this->DrawRectangle(x, y, width, height, color);
				this->DrawRectangle(x - 1, y - 1, width + 2, height + 2, outlineColor);
			}

			void ISurfaceQueuedRenderer::FillOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor) {
				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->DrawRectangle(x, y, width, height, outlineColor);
				this->FillRectangle(x + 1, y + 1, width - 2, height - 2, color);
			}
		}
	}
}