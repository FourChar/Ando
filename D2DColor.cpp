#include "D2DColor.hpp"
#include "Helpers.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			namespace direct2d {
				D2DColor::D2DColor(ID2D1HwndRenderTarget *renderTarget, ando::Color andoColor) {
					this->andoColor = andoColor;

					renderTarget->CreateSolidColorBrush(D2D1::ColorF(andoColor.rgb(), (float)andoColor.a() / 255.0f), &this->color);
				}
				D2DColor::~D2DColor() {
				}

				ando::Color D2DColor::getAndoColor() {
					return this->andoColor;
				}
				ID2D1SolidColorBrushPtr D2DColor::getColor() {
					return this->color;
				}
			}
		}
	}
}