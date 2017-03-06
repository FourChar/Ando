#include "D2DOverlay.hpp"
#include "Helpers.hpp"

#include <string>
#include <locale>
#include <codecvt>

#undef DrawText
#undef DrawTextA

std::vector<std::string> fontList = {
	"Arial",
	"Comic Sans MS",
	"Fixedsys",
	"System",
	"Segoe UI",
	"Segoe Print",
	"Times New Roman",
	"Visitor TT2 BRK"
};

namespace ando {
	namespace overlay {
		namespace concrete {
			D2DOverlay::D2DOverlay() : factory(nullptr), renderTarget(nullptr) {

			}

			bool D2DOverlay::initialize() {
				if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->factory)))
					return false;
				printf("[D2D] Created Factory\r\n");

				if (!IsWindow(this->localInstance.getHwnd())) {
					printf("Local Instance isn't Window!\r\n");
					return false;
				}

				D2D1_SIZE_U size = D2D1::Size<UINT32>(this->localInstance.getWidth(), this->localInstance.getHeight());

				if (FAILED(this->factory->CreateHwndRenderTarget(
						D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
						D2D1::HwndRenderTargetProperties(this->localInstance.getHwnd(), size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
						&this->renderTarget))) {
					this->onDestroy();
					return false;
				}
				printf("[D2D] Created Render Target\r\n");

				if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(this->writeFactory), reinterpret_cast<IUnknown **>(&this->writeFactory)))) {
					this->onDestroy();
					return false;
				}
				printf("[D2D] Created Write Factory\r\n");

				return true;
			}

			bool D2DOverlay::BeginFrame() {
				this->renderTarget->BeginDraw();
				this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
				this->renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black, 0.0f));
				return true;
			}
			bool D2DOverlay::EndFrame() {
				this->renderTarget->EndDraw();
				return true;
			}

			void D2DOverlay::onDestroy() {
				SafeRelease(&this->renderTarget);
				SafeRelease(&this->factory);

				for (std::vector<direct2d::D2DColor*>::iterator it = this->colors.begin(); it != this->colors.end(); it++)
					delete (*it);
				this->colors.clear();

				this->releaseFonts();
			}
			void D2DOverlay::onReset() {

			}
			void D2DOverlay::onRelease() {

			}
			void D2DOverlay::onResize() {
				this->alignToTarget();

				if (!this->renderTarget)
					return;

				this->renderTarget->Resize(D2D1::SizeU(this->localInstance.getWidth(), this->localInstance.getHeight()));
			}

			bool D2DOverlay::FontInitializer(const ando::overlay::surface::ISurfaceFont *font) {
				if (font->isInitialized())
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

				if (result)
					printf("Created Font: %s (Size: %d)\r\n", font->getName().c_str(), font->getSize());
				else
					printf("Failed to create Font: %s\r\n", font->getName().c_str());

				return result;
			}

			void D2DOverlay::DrawRawString(float x, float y, uint8_t size, bool centered, ando::Color color, ando::overlay::surface::ISurfaceFont *font, const char *string) {
				if (!font->isInitialized()) {
					printf("[WARNING] Font not initialized (%s)!\r\n", font->getName().c_str());
					return;
				}

				stringConvertor conv;

				const std::size_t length = strlen(string);
				if (length <= 0)
					return;

				D2D1_RECT_F rect = D2D1::RectF
									(
										float(x),
										float(y),
										this->localInstance.getWidth<float>(),
										this->localInstance.getHeight<float>()
									);

				IDWriteTextFormat *actualFont = (IDWriteTextFormat *)(*font->getFont());

				DWRITE_TEXT_ALIGNMENT textAlignment = actualFont->GetTextAlignment();
				DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment = actualFont->GetParagraphAlignment();

				if (centered) {
					actualFont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
					actualFont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				}
				else {
					actualFont->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
					actualFont->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				}

				this->renderTarget->DrawText(conv.from_bytes(string).c_str(), length, actualFont, rect, (ID2D1Brush*)(*this->toD2DColor(color).get()));

				if (centered) {
					actualFont->SetTextAlignment(textAlignment);
					actualFont->SetParagraphAlignment(paragraphAlignment);
				}
			}
			void D2DOverlay::DrawLine(float x1, float y1, float x2, float y2, ando::Color color) {
				this->renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), (*this->toD2DColor(color).get()), 0.5f);
			}
			void D2DOverlay::DrawRectangle(float x, float y, float width, float height, ando::Color color) {
				D2D1_RECT_F rect = D2D1::RectF(x, y, x + width, y + height);

				D2D1_ANTIALIAS_MODE oldMode = this->renderTarget->GetAntialiasMode();
				this->renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
				this->renderTarget->DrawRectangle(&rect, (*this->toD2DColor(color).get()));
				this->renderTarget->SetAntialiasMode(oldMode);
			}
			void D2DOverlay::FillRectangle(float x, float y, float width, float height, ando::Color color) {
				D2D1_RECT_F rect = D2D1::RectF(x, y, x + width, y + height);

				D2D1_ANTIALIAS_MODE oldMode = this->renderTarget->GetAntialiasMode();
				this->renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
				this->renderTarget->FillRectangle(&rect, (*this->toD2DColor(color).get()));
				this->renderTarget->SetAntialiasMode(oldMode);
			}

			std::shared_ptr<ID2D1SolidColorBrush *> D2DOverlay::toD2DColor(ando::Color andoColor) {
				for (std::size_t i = 0; i < this->colors.size(); i++) {
					direct2d::D2DColor *color = this->colors.at(i);

					if (color->getAndoColor() != andoColor)
						continue;

					return color->getColor();
				}

				this->colors.push_back(new direct2d::D2DColor(this->renderTarget, andoColor));
				return this->colors.at(this->colors.size() - 1)->getColor();
			}

			IDWriteFactory *D2DOverlay::getWriteFactory() {
				return this->writeFactory;
			}
		}
	}
}