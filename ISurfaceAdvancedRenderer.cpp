#include "ISurfaceAdvancedRenderer.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			void ISurfaceAdvancedRenderer::DrawRawString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ISurfaceFont> font, const char *string) {
				ISurfaceBasicRenderer::DrawRawString(coordinates.getX(), coordinates.getY(), size, centered, color, font, string);
			}

			void ISurfaceAdvancedRenderer::DrawString(ando::math::Vector2<float> coordinates, ando::Color color, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawString(coordinates.getX(), coordinates.getY(), color, fontName, buffer);
			}
			void ISurfaceAdvancedRenderer::DrawString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawString(coordinates.getX(), coordinates.getY(), size, centered, color, fontName, buffer);
			}


			void ISurfaceAdvancedRenderer::DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(coordinates.getX(), coordinates.getY(), size, centered, color, outlineColor, fontName, buffer);
			}
			void ISurfaceAdvancedRenderer::DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(coordinates.getX(), coordinates.getY(), size, centered, color, fontName, buffer);
			}
			void ISurfaceAdvancedRenderer::DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, ando::Color color, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(coordinates.getX(), coordinates.getY(), size, color, fontName, buffer);
			}
			void ISurfaceAdvancedRenderer::DrawOutlinedString(ando::math::Vector2<float> coordinates, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(coordinates.getX(), coordinates.getY(), color, outlineColor, fontName, buffer);
			}
			void ISurfaceAdvancedRenderer::DrawOutlinedString(ando::math::Vector2<float> coordinates, ando::Color color, ::std::string fontName, const char *format, ...) {
				FORMAT_STRING(256);

				this->DrawOutlinedString(coordinates.getX(), coordinates.getY(), color, fontName, buffer);
			}

			void ISurfaceAdvancedRenderer::DrawLine(ando::math::Vector2<float> startCoordinates, ando::math::Vector2<float> endCoordinates, ando::Color color) {
				ISurfaceBasicRenderer::DrawLine(startCoordinates.getX(), startCoordinates.getY(), endCoordinates.getX(), endCoordinates.getY(), color);
			}

			void ISurfaceAdvancedRenderer::DrawOutlinedLine(ando::math::Vector2<float> startCoordinates, ando::math::Vector2<float> endCoordinates, ando::Color color, ando::Color outlineColor) {
				this->DrawOutlinedLine(startCoordinates.getX(), startCoordinates.getY(), endCoordinates.getX(), endCoordinates.getY(), color, outlineColor);
			}

			void ISurfaceAdvancedRenderer::DrawRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color) {
				ISurfaceBasicRenderer::DrawRectangle(coordinates.getX(), coordinates.getY(), size.getX(), size.getY(), color);
			}
			void ISurfaceAdvancedRenderer::DrawRectangle(ando::math::Rect<float> rect, ando::Color color) {
				ISurfaceBasicRenderer::DrawRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), color);
			}

			void ISurfaceAdvancedRenderer::FillRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color) {
				ISurfaceBasicRenderer::FillRectangle(coordinates.getX(), coordinates.getY(), size.getX(), size.getY(), color);
			}
			void ISurfaceAdvancedRenderer::FillRectangle(ando::math::Rect<float> rect, ando::Color color) {
				ISurfaceBasicRenderer::FillRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), color);
			}

			void ISurfaceAdvancedRenderer::DrawOutlinedRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color, ando::Color outlineColor) {
				this->DrawOutlinedRectangle(coordinates.getX(), coordinates.getY(), size.getX(), size.getY(), color, outlineColor);
			}
			void ISurfaceAdvancedRenderer::DrawOutlinedRectangle(ando::math::Rect<float> rect, ando::Color color, ando::Color outlineColor) {
				this->DrawOutlinedRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), color, outlineColor);
			}

			void ISurfaceAdvancedRenderer::FillOutlinedRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color, ando::Color outlineColor) {
				this->FillOutlinedRectangle(coordinates.getX(), coordinates.getY(), size.getX(), size.getY(), color, outlineColor);
			}
			void ISurfaceAdvancedRenderer::FillOutlinedRectangle(ando::math::Rect<float> rect, ando::Color color, ando::Color outlineColor) {
				this->FillOutlinedRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), color, outlineColor);
			}

			void ISurfaceAdvancedRenderer::DrawProgressBar(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, float percentage, ando::Color successColor, ando::Color failureColor) {
				this->DrawProgressBar(coordinates.getX(), coordinates.getY(), size.getX(), size.getY(), percentage, successColor, failureColor);
			}
			void ISurfaceAdvancedRenderer::DrawProgressBar(ando::math::Rect<float> rect, float percentage, ando::Color successColor, ando::Color failureColor) {
				this->DrawProgressBar(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), percentage, successColor, failureColor);
			}

			void ISurfaceAdvancedRenderer::DrawOutlinedProgressBar(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, float percentage, ando::Color successColor, ando::Color failureColor, ando::Color outlineColor) {
				this->DrawOutlinedProgressBar(coordinates.getX(), coordinates.getY(), size.getX(), size.getY(), percentage, successColor, failureColor, outlineColor);
			}
			void ISurfaceAdvancedRenderer::DrawOutlinedProgressBar(ando::math::Rect<float> rect, float percentage, ando::Color successColor, ando::Color failureColor, ando::Color outlineColor) {
				this->DrawOutlinedProgressBar(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), percentage, successColor, failureColor, outlineColor);
			}
		}
	}
}