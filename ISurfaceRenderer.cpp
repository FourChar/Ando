#include "ISurfaceRenderer.hpp"

#include <cstdarg>
#include <thread>

#define FORMAT_STRING(s)		char buffer[s] = {0}; { va_list args; va_start(args, format); vsprintf_s(buffer, format, args); va_end(args); }

namespace ando {
	namespace overlay {
		namespace surface {
			ISurfaceRenderer::ISurfaceRenderer() { }

			void ISurfaceRenderer::waitForEmptyQueue() const {
				while (!this->renderQueue.isQueueEmpty());
			}

			std::shared_ptr<ISurfaceFont> ISurfaceRenderer::getFont(const std::string name, const uint8_t size) const {
				for (std::size_t i = 0; i < this->fonts.size(); i++) {
					auto font = this->fonts.at(i);

					if ((font->getName().compare(name) != 0) || (font->getSize() != size))
						continue;
					
					return font;
				}

				return nullptr;
			}
			std::shared_ptr<ISurfaceFont> ISurfaceRenderer::addFont(const std::string name, const uint8_t size, const uint16_t weight, const bool italics) {
				if (name.empty())
					return nullptr;

				std::shared_ptr<ISurfaceFont> newFont = std::make_shared<ISurfaceFont>(name, size, weight, italics, std::bind(&ando::overlay::surface::ISurfaceRenderer::FontInitializer, this, std::placeholders::_1));
				
				this->fonts.push_back(newFont);

				return newFont;
			}
			void ISurfaceRenderer::releaseFonts() {
				for (std::size_t i = 0; i < this->fonts.size(); i++) {
					auto font = this->fonts.at(i);

					void **actualFont = font->getFont();
					//SafeRelease(actualFont);

					this->fonts.erase(this->fonts.begin() + i);
				}
			}

			void ISurfaceRenderer::DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, std::string fontName, const char * format, ...) {
				std::shared_ptr<ISurfaceFont> font = this->getFont(fontName, size);
				if (!font) {
					font = this->addFont(fontName, size, ISURFACE_TEXT_WEIGHT_DEFAULT, ISURFACE_TEXT_ITALICS_DEFAULT);

					if (!font)
						return;
				}

				FORMAT_STRING(256);

				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->renderQueue.DrawRawString(x - 1, y - 1, size, centered, outlineColor, font, buffer);
				this->renderQueue.DrawRawString(x - 1, y + 1, size, centered, outlineColor, font, buffer);
				this->renderQueue.DrawRawString(x + 1, y - 1, size, centered, outlineColor, font, buffer);
				this->renderQueue.DrawRawString(x + 1, y + 1, size, centered, outlineColor, font, buffer);
				this->renderQueue.DrawRawString(x, y, size, centered, color, font, buffer);
			}
			void ISurfaceRenderer::DrawOutlinedString(float x, float y, uint8_t size, bool centered, ando::Color color, std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, size, centered, color, ando::colors::black, fontName, buffer);
			}
			void ISurfaceRenderer::DrawOutlinedString(float x, float y, uint8_t size, ando::Color color, std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, size, ISURFACE_TEXT_CENTERED_DEFAULT, color, fontName, buffer);
			}
			void ISurfaceRenderer::DrawOutlinedString(float x, float y, ando::Color color, ando::Color outlineColor, std::string fontName, const char * format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, ISURFACE_TEXT_SIZE_DEFAULT, ISURFACE_TEXT_CENTERED_DEFAULT, color, outlineColor, fontName, buffer);
			}
			void ISurfaceRenderer::DrawOutlinedString(float x, float y, ando::Color color, std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(x, y, ISURFACE_TEXT_SIZE_DEFAULT, ISURFACE_TEXT_CENTERED_DEFAULT, color, ando::colors::black, fontName, buffer);
			}

			void ISurfaceRenderer::DrawString(float x, float y, ando::Color color, std::string fontName, const char *format, ...) {
				std::shared_ptr<ISurfaceFont> font = this->getFont(fontName, ISURFACE_TEXT_SIZE_DEFAULT);
				if (!font) {
					font = this->addFont(fontName, ISURFACE_TEXT_SIZE_DEFAULT, ISURFACE_TEXT_WEIGHT_DEFAULT, ISURFACE_TEXT_ITALICS_DEFAULT);

					if (!font)
						return;
				}

				FORMAT_STRING(256);

				this->renderQueue.DrawRawString(x, y, ISURFACE_TEXT_SIZE_DEFAULT, false, color, font, buffer);
			}
			void ISurfaceRenderer::DrawString(float x, float y, uint8_t size, bool centered, ando::Color color, std::string fontName, const char *format, ...) {
				std::shared_ptr<ISurfaceFont> font = this->getFont(fontName, size);
				if (!font) {
					font = this->addFont(fontName, size, ISURFACE_TEXT_WEIGHT_DEFAULT, ISURFACE_TEXT_ITALICS_DEFAULT);

					if (!font)
						return;
				}

				FORMAT_STRING(256);

				this->renderQueue.DrawRawString(x, y, size, centered, color, font, buffer);
			}

			void ISurfaceRenderer::DrawOutlinedLine(float x1, float y1, float x2, float y2, ando::Color color, ando::Color outlineColor) {
				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->renderQueue.DrawLine(x1 - 1, y1 - 1, x2 - 1, y2 - 1, outlineColor);
				this->renderQueue.DrawLine(x1, y1, x2, y2, color);
			}

			void ISurfaceRenderer::DrawOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor) {
				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->renderQueue.DrawRectangle(x + 1, y + 1, width - 2, height - 2, outlineColor);
				this->renderQueue.DrawRectangle(x, y, width, height, color);
				this->renderQueue.DrawRectangle(x - 1, y - 1, width + 2, height + 2, outlineColor);
			}

			void ISurfaceRenderer::FillOutlinedRectangle(float x, float y, float width, float height, ando::Color color, ando::Color outlineColor) {
				outlineColor.setA(ISURFACE_OUTLINE_ALPHA);

				this->renderQueue.DrawRectangle(x, y, width, height, outlineColor);
				this->renderQueue.FillRectangle(x + 1, y + 1, width - 2, height - 2, color);
			}
		}
	}
}