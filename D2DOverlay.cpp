#include "D2DOverlay.hpp"
#include "Helpers.hpp"

#include <string>
#include <locale>
#include <codecvt>


#ifdef UNICODE
#define DrawText  DrawTextW
#else
#define DrawText  DrawTextA
#endif // !UNICODE

namespace ando {
	namespace overlay {
		namespace concrete {
			using logger::ELogLevel;

			D2DOverlay::D2DOverlay() : factory(nullptr), renderTarget(nullptr) { }
			D2DOverlay::D2DOverlay(::std::shared_ptr<logger::ILogger> logger) : factory(nullptr), renderTarget(nullptr), Overlay(logger) { }
			D2DOverlay::~D2DOverlay() {
				this->onDestroy();
			}

			bool D2DOverlay::initialize() {
				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::initialize} Creating D2D Factory...");
				if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->factory))) {
					this->logger->log(ELogLevel::LOG_ERROR, "Failed to create D2D Factory!");
					return false;
				}

				if (!IsWindow(this->getLocal()->getHwnd())) {
					this->logger->log(ELogLevel::LOG_CRITICAL, "{D2DOverlay::initialize} Local Instance isn't Window!");
					return false;
				}

				D2D1_SIZE_U size = ::D2D1::Size<UINT32>(this->getLocal()->getWidth(), this->getLocal()->getHeight());

				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::initialize} Creating D2D RenderTarget...");
				if (FAILED(this->factory->CreateHwndRenderTarget(
						::D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, ::D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
						::D2D1::HwndRenderTargetProperties(this->getLocal()->getHwnd(), size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
						&this->renderTarget))) {
					this->logger->log(ELogLevel::LOG_ERROR, "{D2DOverlay::initialize} Failed to create D2D RenderTarget!");
					this->onDestroy();
					return false;
				}

				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::initialize} Creating D2D WriteFactory...");
				if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(this->writeFactory), reinterpret_cast<IUnknown **>(&this->writeFactory)))) {
					this->logger->log(ELogLevel::LOG_ERROR, "{D2DOverlay::initialize} Failed to create D2D WriteFactory!");
					this->onDestroy();
					return false;
				}

				return true;
			}

			bool D2DOverlay::BeginFrame() {
				this->renderTarget->BeginDraw();
				this->renderTarget->SetTransform(::D2D1::Matrix3x2F::Identity());
				this->renderTarget->Clear(::D2D1::ColorF(::D2D1::ColorF::Black, 0.0f));
				return true;
			}
			bool D2DOverlay::EndFrame() {
				this->renderTarget->EndDraw();
				return true;
			}

			void D2DOverlay::onDestroy() {
				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::onDestroy} Releasing D2D instance...");
				SafeRelease(&this->renderTarget);
				SafeRelease(&this->factory);

				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::onDestroy} Releasing D2D colors...");
				for (::std::vector<direct2d::D2DColor*>::iterator it = this->colors.begin(); it != this->colors.end(); it++)
					delete (*it);
				this->colors.clear();

				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::onDestroy} Releasing D2D fonts...");
				this->releaseFonts();
			}
			void D2DOverlay::onReset() {

			}
			void D2DOverlay::onRelease() {

			}
			void D2DOverlay::onResize() {
				if (!this->renderTarget)
					return;

				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::onResize} Resizing D2D RenderTarget...");
				if (FAILED(this->renderTarget->Resize(::D2D1::SizeU(this->getLocal()->getWidth(), this->getLocal()->getHeight())))) {
					this->logger->log(ELogLevel::LOG_WARNING, "{D2DOverlay::onResize} Failed to resize D2D RenderTarget!");
				}
			}

			bool D2DOverlay::FontInitializer(const surface::ISurfaceFont *font) {
				if (font->isInitialized() || font->getName().empty() || font->getSize() <= 0)
					return false;

				IDWriteTextFormat **actualFont = (IDWriteTextFormat **)font->getFont();
				if (actualFont == nullptr)
					return false;

				stringConvertor conv;

				bool result = SUCCEEDED(this->getWriteFactory()->CreateTextFormat(
					conv.from_bytes(font->getName()).c_str(),
					NULL,
					(DWRITE_FONT_WEIGHT)font->getWeight(),
					font->isItalics() ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_NORMAL,
					font->getSize(),
					L"",
					actualFont));

				if (result) {
					this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::FontInitializer} Created Font: %s (Size: %d)", font->getName().c_str(), font->getSize());
				}
				else {
					this->logger->log(ELogLevel::LOG_WARNING, "{D2DOverlay::FontInitializer} Failed to create Font! %s", font->getName().c_str());
				}

				return result;
			}

			void D2DOverlay::DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ::std::shared_ptr<surface::ISurfaceFont> font, const char *string) {
				if (!font->isInitialized()) {
					this->logger->log(ELogLevel::LOG_WARNING, "{D2DOverlay::DrawRawString} Font not initialized! %s", font->getName().c_str());
					return;
				}

				stringConvertor conv;

				const ::std::size_t length = strlen(string);
				if (length <= 0)
					return;

				D2D1_RECT_F rect = ::D2D1::RectF
									(
										float(x),
										float(y),
										this->getLocal()->getWidth<float>(),
										this->getLocal()->getHeight<float>()
									);

				IDWriteTextFormat *actualFont = (IDWriteTextFormat *)(*font->getFont());

				DWRITE_TEXT_ALIGNMENT textAlignment = actualFont->GetTextAlignment();
				DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment = actualFont->GetParagraphAlignment();

				if (centered) {
					actualFont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					//actualFont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				}
				else {
					actualFont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					//actualFont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				}

				this->renderTarget->DrawTextA(conv.from_bytes(string).c_str(), length, actualFont, rect, (ID2D1Brush*)this->toD2DColor(color));

				if (centered) {
					actualFont->SetTextAlignment(textAlignment);
					actualFont->SetParagraphAlignment(paragraphAlignment);
				}
			}

			void D2DOverlay::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
				this->renderTarget->DrawLine(::D2D1::Point2F(x1, y1), ::D2D1::Point2F(x2, y2), this->toD2DColor(color), 0.5f);
			}
			void D2DOverlay::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
				D2D1_RECT_F rect = ::D2D1::RectF(x, y, x + height, y + width);

				D2D1_ANTIALIAS_MODE oldMode = this->renderTarget->GetAntialiasMode();
				this->renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
				this->renderTarget->DrawRectangle(&rect, this->toD2DColor(color));
				this->renderTarget->SetAntialiasMode(oldMode);
			}
			void D2DOverlay::FillRectangle(float x, float y, float width, float height, ando::Color color) {
				D2D1_RECT_F rect = ::D2D1::RectF(x - 1, y - 1, x + height, y + width);

				D2D1_ANTIALIAS_MODE oldMode = this->renderTarget->GetAntialiasMode();
				this->renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
				this->renderTarget->FillRectangle(&rect, this->toD2DColor(color));
				this->renderTarget->SetAntialiasMode(oldMode);
			}

			ID2D1SolidColorBrushPtr D2DOverlay::toD2DColor(ando::Color andoColor) {
				for (::std::size_t i = 0; i < this->colors.size(); i++) {
					direct2d::D2DColor *color = this->colors.at(i);

					if (color->getAndoColor() != andoColor)
						continue;

					return color->getColor();
				}

				this->logger->log(ELogLevel::LOG_DEBUG, "{D2DOverlay::toD2DColor} Caching new D2DColor (%u, %u, %u, %u)...", andoColor.r(), andoColor.g(), andoColor.b(), andoColor.a());

				this->colors.emplace_back(new direct2d::D2DColor(this->renderTarget, andoColor));
				return this->colors.at(this->colors.size() - 1)->getColor();
			}

			IDWriteFactoryPtr D2DOverlay::getWriteFactory() const {
				return this->writeFactory;
			}
		}
	}
}