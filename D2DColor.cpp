#include "D2DColor.hpp"
#include "Helpers.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			namespace direct2d {
				D2DColor::D2DColor(ID2D1HwndRenderTarget *renderTarget, ando::Color andoColor) {
					this->andoColor = andoColor;

					ID2D1SolidColorBrush *temp = nullptr;
					renderTarget->CreateSolidColorBrush(D2D1::ColorF(andoColor.rgb(), (float)andoColor.a() / 255.0f), &temp);
					this->color = std::make_shared<ID2D1SolidColorBrush *>(temp);
				}
				D2DColor::~D2DColor() {
					if (this->color)
						(*this->color)->Release();
				}

				ando::Color D2DColor::getAndoColor() {
					return this->andoColor;
				}
				std::shared_ptr<ID2D1SolidColorBrush *> D2DColor::getColor() {
					return this->color;
				}
			}
		}
	}
}