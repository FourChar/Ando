#ifndef ISURFACE_QUEUED_RENDERER
#define ISURFACE_QUEUED_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include "ISurfaceAdvancedRenderer.hpp"
#include "ISurfaceFontRenderer.hpp"
#include "ISurfaceQueue.hpp"
#include "ISurfaceFont.hpp"
#include "Color.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceQueuedRenderer : public ISurfaceAdvancedRenderer {
			protected:
				ando::overlay::surface::ISurfaceFontRenderer *renderer;
				std::shared_ptr<ando::overlay::surface::queue::ISurfaceQueue> renderQueue;

			public:
				ISurfaceQueuedRenderer(ando::overlay::surface::ISurfaceFontRenderer *renderer);

				std::shared_ptr<ando::overlay::surface::queue::ISurfaceQueue> getRenderQueue();

			public: // wtf c++ devs... stop being lazy and make the compiler look through all parent classes -.- or at least give an option to make the compiler do so..
				virtual void DrawRawString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<ISurfaceFont> font, const char *string) {
					ISurfaceAdvancedRenderer::DrawRawString(coordinates, size, centered, color, font, string);
				}
				virtual void DrawString(ando::math::Vector2<float> coordinates, ando::Color color, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawString(coordinates, color, fontName, buffer);
				}
				virtual void DrawString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawString(coordinates, size, centered, color, fontName, buffer);
				}
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawOutlinedString(coordinates, size, centered, color, outlineColor, fontName, buffer);
				}
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, bool centered, ando::Color color, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawOutlinedString(coordinates, size, centered, color, fontName, buffer);
				}
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, uint8_t size, ando::Color color, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawOutlinedString(coordinates, size, color, fontName, buffer);
				}
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, ando::Color color, ando::Color outlineColor, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawOutlinedString(coordinates, color, outlineColor, fontName, buffer);
				}
				virtual void DrawOutlinedString(ando::math::Vector2<float> coordinates, ando::Color color, ::std::string fontName, const char *format, ...) {
					FORMAT_STRING(256);
					ISurfaceAdvancedRenderer::DrawOutlinedString(coordinates, color, fontName, buffer);
				}

				virtual void DrawLine(ando::math::Vector2<float> startCoordinates, ando::math::Vector2<float> endCoordinates, ando::Color color) {
					ISurfaceAdvancedRenderer::DrawLine(startCoordinates, endCoordinates, color);
				}
				virtual void DrawOutlinedLine(ando::math::Vector2<float> startCoordinates, ando::math::Vector2<float> endCoordinates, ando::Color color, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::DrawOutlinedLine(startCoordinates, endCoordinates, color, outlineColor);
				}

				virtual void DrawRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color) {
					ISurfaceAdvancedRenderer::DrawRectangle(coordinates, size, color);
				}
				virtual void DrawRectangle(ando::math::Rect<float> rect, ando::Color color) {
					ISurfaceAdvancedRenderer::DrawRectangle(rect, color);
				}
				virtual void DrawOutlinedRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::DrawOutlinedRectangle(coordinates, size, color, outlineColor);
				}
				virtual void DrawOutlinedRectangle(ando::math::Rect<float> rect, ando::Color color, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::DrawOutlinedRectangle(rect, color, outlineColor);
				}

				virtual void FillRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color) {
					ISurfaceAdvancedRenderer::FillRectangle(coordinates, size, color);
				}
				virtual void FillRectangle(ando::math::Rect<float> rect, ando::Color color) {
					ISurfaceAdvancedRenderer::FillRectangle(rect, color);
				}
				virtual void FillOutlinedRectangle(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, ando::Color color, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::FillOutlinedRectangle(coordinates, size, color, outlineColor);
				}
				virtual void FillOutlinedRectangle(ando::math::Rect<float> rect, ando::Color color, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::FillOutlinedRectangle(rect, color, outlineColor);
				}

				virtual void DrawProgressBar(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible) {
					ISurfaceAdvancedRenderer::DrawProgressBar(coordinates, size, percentage, successColor, failureColor);
				}
				virtual void DrawProgressBar(ando::math::Rect<float> rect, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible) {
					ISurfaceAdvancedRenderer::DrawProgressBar(rect, percentage, successColor, failureColor);
				}
				virtual void DrawOutlinedProgressBar(ando::math::Vector2<float> coordinates, ando::math::Vector2<float> size, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::DrawOutlinedProgressBar(coordinates, size, percentage, successColor, failureColor, outlineColor);
				}
				virtual void DrawOutlinedProgressBar(ando::math::Rect<float> rect, float percentage, ando::Color successColor = ando::colors::green, ando::Color failureColor = ando::colors::invisible, ando::Color outlineColor = ando::colors::black) {
					ISurfaceAdvancedRenderer::DrawOutlinedProgressBar(rect, percentage, successColor, failureColor, outlineColor);
				}

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