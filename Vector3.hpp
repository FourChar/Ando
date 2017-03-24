#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include "Vector2.hpp"

namespace ando {
	namespace math {
		template <typename T = float>
		class Vector3 : public Vector2<T> {
		protected: // Variables
			T _3;

		public: // Constructors
			Vector3() : Vector2() {
				this->_3 = 0;
			}
			Vector3(const T all) : Vector2(all) {
				this->_3 = all;
			}
			Vector3(const T _1, const T _2, const T _3) : Vector2(_1, _2) {
				this->_3 = _3;
			}

		public: // Operators
			Vector3<T> &operator=(const Vector3<T> &rhs) {
				ando::math::Vector2<T>::operator=(rhs);
				this->_3 = rhs._3;
				return (*this);
			}
			Vector3<T> operator+(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 + rhs._1, this->_2 + rhs._2, this->_3 + rhs._3);
			}
			Vector3<T> operator -(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 - rhs._1, this->_2 - rhs._2, this->_3 - rhs._3);
			}
			Vector3<T> operator *(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 * rhs._1, this->_2 * rhs._2, this->_3 * rhs._3);
			}
			Vector3<T> operator /(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 / rhs._1, this->_2 / rhs._2, this->_3 / rhs._3);
			}
			Vector3<T> operator %(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 % rhs._1, this->_2 % rhs._2, this->_3 % rhs._3);
			}
			Vector3<T> operator ^(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 ^ rhs._1, this->_2 ^ rhs._2, this->_3 ^ rhs._3);
			}
			Vector3<T> operator &(const Vector3<T> &rhs) {
				return Vector3<T>(this->_1 & rhs._1, this->_2 & rhs._2, this->_3 & rhs._3);
			}
			operator bool() {
				return (this->_1 != 0.0f) && (this->_2 != 0.0f) && (this->_3 != 0.0f);
			}
			bool operator !() {
				return (this->_1 == 0.0f) && (this->_2 == 0.0f) && (this->_3 == 0.0f);
			}

			Vector3<T> &operator +=(const Vector3<T> &rhs) {
				Vector2<T>::operator+=(rhs);
				this->_3 += rhs._3;
				return (*this);
			}
			Vector3<T> &operator -=(const Vector3<T> &rhs) {
				Vector2<T>::operator-=(rhs);
				this->_3 -= rhs._3;
				return (*this);
			}
			Vector3<T> &operator *=(const Vector3<T> &rhs) {
				Vector2<T>::operator*=(rhs);
				this->_3 *= rhs._3;
				return (*this);
			}
			Vector3<T> &operator /=(const Vector3<T> &rhs) {
				Vector2<T>::operator/=(rhs);
				this->_3 /= rhs._3;
				return (*this);
			}
			Vector3<T> &operator %=(const Vector3<T> &rhs) {
				Vector2<T>::operator%=(rhs);
				this->_3 %= rhs._3;
				return (*this);
			}
			Vector3<T> &operator ^=(const Vector3<T> &rhs) {
				Vector2<T>::operator^=(rhs);
				this->_3 ^= rhs._3;
				return (*this);
			}
			Vector3<T> &operator &=(const Vector3<T> &rhs) {
				Vector2<T>::operator&=(rhs);
				this->_3 &= rhs._3;
				return (*this);
			}
			bool operator !=(const Vector3<T> &rhs) {
				return (this->_1 != rhs._1) || (this->_2 != rhs._2) || (this->_3 != rhs._3);
			}
			bool operator ==(const Vector3<T> &rhs) {
				return (this->_1 == rhs._1) && (this->_2 == rhs._2) && (this->_3 == rhs._3);
			}
			T &operator[](const int index) {
				switch (index) {
				case 0:
					return this->_1;
				case 1:
					return this->_2;
				case 2:
					return this->_3;
				}

				return this->_1;
			}

		public: // Functions
			virtual T distanceTo(const Vector3<T> &rhs) {
				Vector3<T> distance((this->_1 - rhs._1), (this->_2 - rhs._2), (this->_3 - rhs._3));

				return (float)sqrt((distance.getX() * distance.getX()) +
					(distance.getY() * distance.getY()) +
					(distance.getZ() * distance.getZ()));
			}

		public: // Getters
			T getZ() const {
				return this->_3;
			}

			T *getZData() {
				return &this->_3;
			}

		public: // Setters
			void setZ(const T _3) {
				this->_3 = _3;
			}
		};
	}
}

#endif // VECTOR3_HPP