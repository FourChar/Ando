#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "Vector2.hpp"
#include "Vector3.hpp"

namespace ando {
	namespace math {
		template <typename T>
		class Vector4 : public Vector3<T> {
		protected: // Variables
			T _4;

		public: // Constructors
			Vector4() : Vector3() {
				this->_4 = 0;
			}
			Vector4(const T all) : Vector3(all) {
				this->_4 = all;
			}
			Vector4(const T _1, const T _2, const T _3, const T _4) : Vector3(_1, _2, _3) {
				this->_4 = _4;
			}

		public: // Operators
			Vector4<T> &operator=(const Vector4<T> &rhs) {
				ando::math::Vector3<T>::operator=(rhs);
				this->_4 = rhs._4;
				return (*this);
			}
			Vector4<T> operator+(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 + rhs._1, this->_2 + rhs._2, this->_3 + rhs._3, this->_4 + rhs._4);
			}
			Vector4<T> operator -(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 - rhs._1, this->_2 - rhs._2, this->_3 - rhs._3, this->_4 - rhs._4);
			}
			Vector4<T> operator *(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 * rhs._1, this->_2 * rhs._2, this->_3 * rhs._3, this->_4 * rhs._4);
			}
			Vector4<T> operator /(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 / rhs._1, this->_2 / rhs._2, this->_3 / rhs._3, this->_4 / rhs._4);
			}
			Vector4<T> operator %(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 % rhs._1, this->_2 % rhs._2, this->_3 % rhs._3, this->_4 % rhs._4);
			}
			Vector4<T> operator ^(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 ^ rhs._1, this->_2 ^ rhs._2, this->_3 ^ rhs._3, this->_4 ^ rhs._4);
			}
			Vector4<T> operator &(const Vector4<T> &rhs) {
				return Vector4<T>(this->_1 & rhs._1, this->_2 & rhs._2, this->_3 & rhs._3, this->_4 & rhs._4);
			}
			operator bool() {
				return (this->_1 != 0.0f) && (this->_2 != 0.0f) && (this->_3 != 0.0f) && (this->_4 != 0.0f);
			}
			bool operator !() {
				return (this->_1 == 0.0f) && (this->_2 == 0.0f) && (this->_3 == 0.0f) && (this->_4 == 0.0f);
			}

			Vector4<T> &operator +=(const Vector4<T> &rhs) {
				Vector3<T>::operator+=(rhs);
				this->_4 += rhs._4;
				return (*this);
			}
			Vector4<T> &operator -=(const Vector4<T> &rhs) {
				Vector3<T>::operator-=(rhs);
				this->_4 -= rhs._4;
				return (*this);
			}
			Vector4<T> &operator *=(const Vector4<T> &rhs) {
				Vector3<T>::operator*=(rhs);
				this->_4 *= rhs._4;
				return (*this);
			}
			Vector4<T> &operator /=(const Vector4<T> &rhs) {
				Vector3<T>::operator/=(rhs);
				this->_4 /= rhs._4;
				return (*this);
			}
			Vector4<T> &operator %=(const Vector4<T> &rhs) {
				Vector3<T>::operator%=(rhs);
				this->_4 %= rhs._4;
				return (*this);
			}
			Vector4<T> &operator ^=(const Vector4<T> &rhs) {
				Vector3<T>::operator^=(rhs);
				this->_4 ^= rhs._4;
				return (*this);
			}
			Vector4<T> &operator &=(const Vector4<T> &rhs) {
				Vector3<T>::operator&=(rhs);
				this->_4 &= rhs._4;
				return (*this);
			}
			bool operator !=(const Vector4<T> &rhs) {
				return (this->_1 != rhs._1) || (this->_2 != rhs._2) || (this->_3 != rhs._3) || (this->_4 != rhs._4);
			}
			bool operator ==(const Vector4<T> &rhs) {
				return (this->_1 == rhs._1) && (this->_2 == rhs._2) && (this->_3 == rhs._3) && (this->_4 == rhs._4);
			}
			T &operator[](const int index) {
				switch (index) {
				case 0:
					return this->_1;
				case 1:
					return this->_2;
				case 2:
					return this->_3;
				case 3:
					return this->_4;
				}

				return this->_1;
			}

		public: // Functions
			virtual T distanceTo(const Vector4<T> &rhs) {
				Vector4<T> distance((this->_1 - rhs._1), (this->_2 - rhs._2), (this->_3 - rhs._3), (this->_4 - rhs._4));

				return (float)sqrt((distance.getX() * distance.getX()) +
					(distance.getY() * distance.getY()) +
					(distance.getZ() * distance.getZ()) +
					(distance.getW() * distance.getW()));
			}

			static int getSize() {
				return sizeof(T) * 4;
			}

		public: // Getters
			T getW() const {
				return this->_4;
			}

			T *getWData() {
				return &this->_4;
			}

		public: // Setters
			void setW(const T _4) {
				this->_4 = _4;
			}
		};
	}
}

#endif // VECTOR4_HPP
