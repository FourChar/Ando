#ifndef D2D_COLOR_HPP
#define D2D_COLOR_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>
#include <d2d1.h>

#include "Color.hpp"

namespace ando {
	namespace overlay {
		namespace concrete {
			namespace direct2d {
				class D2DColor {
				private:
					ando::Color andoColor;
					std::shared_ptr<ID2D1SolidColorBrush *> color;

				public:
					D2DColor(ID2D1HwndRenderTarget *renderTarget, ando::Color andoColor);
					~D2DColor();

					ando::Color getAndoColor();
					std::shared_ptr<ID2D1SolidColorBrush *> getColor();
				};
			}
			}
	}
}

#endif // D2D_COLOR_HPP