#ifndef ANDO_MATH_UTILS_HPP
#define ANDO_MATH_UTILS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "Matrix.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Rect.hpp"

namespace ando {
	namespace math {
		bool worldToScreen(Matrix<float, 4, 4> viewMatrix, Vector3<float> from, Vector2<float> &to, Rect<float> screenRect) {
			float w = (viewMatrix[12] * from[0]) + (viewMatrix[13] * from[1]) + (viewMatrix[14] * from[2]) + viewMatrix[15];

			if (w < 0.01f)
				return false;

			to[0] = (viewMatrix[0] * from[0]) + (viewMatrix[1] * from[1]) + (viewMatrix[2] * from[2]) + viewMatrix[3];
			to[1] = (viewMatrix[4] * from[0]) + (viewMatrix[5] * from[1]) + (viewMatrix[6] * from[2]) + viewMatrix[7];

			float invertedW = 1.0f / w;

			to[0] *= invertedW;
			to[1] *= invertedW;

			Vector2<float> screenCenter(screenRect.getWidth() / 2.0f, screenRect.getHeight() / 2.0f);

			screenCenter[0] += (0.5f * to[0] * screenRect.getWidth()) + 0.5f;
			screenCenter[1] -= (0.5f * to[1] * screenRect.getHeight()) + 0.5f;

			to[0] = screenRect.getX() + screenCenter.getX();
			to[1] = screenRect.getY() + screenCenter.getY();
			return true;
		}
	}
}

#endif // ANDO_MATH_UTILS_HPP