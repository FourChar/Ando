#ifndef RECT_HPP
#define RECT_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "Vector4.hpp"

namespace ando {
	namespace math {
		template <typename T>
		class Rect : public Vector4<T> {
		public: // Constructors
			Rect() : Vector4() { }
			Rect(const T all) : Vector4(all) { }
			Rect(const T _1, const T _2, const T _3, const T _4) : Vector4(_1, _2, _3, _4) { }

		public: // Getters
			T getWidth() const {
				return this->getZ();
			}
			T getHeight() const {
				return this->getW();
			}

		public: // Setters
			void setWidth(const T _width) {
				this->setZ(_width);
			}
			void setHeight(const T _height) {
				this->setW(_height);
			}
		};
	}
}

#endif // RECT_HPP
