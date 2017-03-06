#ifndef D2D_COLOR_HPP
#define D2D_COLOR_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>
#include <d2d1.h>
#include <comdef.h>

#include "Color.hpp"

_COM_SMARTPTR_TYPEDEF(ID2D1SolidColorBrush, __uuidof(ID2D1SolidColorBrush));

namespace ando {
	namespace overlay {
		namespace concrete {
			namespace direct2d {
				class D2DColor {
				private:
					ando::Color andoColor;
					ID2D1SolidColorBrushPtr color;

				public:
					D2DColor(ID2D1HwndRenderTarget *renderTarget, ando::Color andoColor);
					~D2DColor();

					ando::Color getAndoColor();
					ID2D1SolidColorBrushPtr getColor();
				};
			}
		}
	}
}

#endif // D2D_COLOR_HPP