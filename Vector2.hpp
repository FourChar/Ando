#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace ando {
	namespace math {
		template <typename T = float>
		class Vector2 {
		protected: // Variables
			T _1;
			T _2;

		public: // Constructors
			Vector2() {
				this->_1 = 0.0f;
				this->_2 = 0.0f;
			}
			Vector2(const T all) {
				this->_1 = all;
				this->_2 = all;
			}
			Vector2(const T _1, const T _2) {
				this->_1 = _1;
				this->_2 = _2;
			}

		public: // Operators
			Vector2<T> &operator=(const T &rhs) {
				this->_1 = rhs;
				this->_2 = rhs;
				return (*this);
			}
			Vector2<T> operator +(const T &rhs) {
				return Vector2<T>(this->_1 + rhs, this->_2 + rhs);
			}
			Vector2<T> operator -(const T &rhs) {
				return Vector2<T>(this->_1 - rhs, this->_2 - rhs);
			}
			Vector2<T> operator *(const T &rhs) {
				return Vector2<T>(this->_1 * rhs, this->_2 * rhs);
			}
			Vector2<T> operator /(const T &rhs) {
				return Vector2<T>(this->_1 / rhs, this->_2 / rhs);
			}
			Vector2<T> operator %(const T &rhs) {
				return Vector2<T>(this->_1 % rhs, this->_2 % rhs);
			}
			Vector2<T> operator ^(const T &rhs) {
				return Vector2<T>(this->_1 ^ rhs, this->_2 ^ rhs);
			}
			Vector2<T> operator &(const T &rhs) {
				return Vector2<T>(this->_1 & rhs, this->_2 & rhs);
			}
			Vector2<T> &operator +=(const T &rhs) {
				this->_1 += rhs;
				this->_2 += rhs;
				return (*this);
			}
			Vector2<T> &operator -=(const T &rhs) {
				this->_1 -= rhs;
				this->_2 -= rhs;
				return (*this);
			}
			Vector2<T> &operator *=(const T &rhs) {
				this->_1 *= rhs;
				this->_2 *= rhs;
				return (*this);
			}
			Vector2<T> &operator /=(const T &rhs) {
				this->_1 /= rhs;
				this->_2 /= rhs;
				return (*this);
			}
			Vector2<T> &operator %=(const T &rhs) {
				this->_1 %= rhs;
				this->_2 %= rhs;
				return (*this);
			}
			Vector2<T> &operator ^=(const T &rhs) {
				this->_1 ^= rhs;
				this->_2 ^= rhs;
				return (*this);
			}
			Vector2<T> &operator &=(const T &rhs) {
				this->_1 &= rhs;
				this->_2 &= rhs;
				return (*this);
			}
			bool operator !=(const T &rhs) {
				return (this->_1 != rhs) || (this->_2 != rhs);
			}
			bool operator ==(const T &rhs) {
				return (this->_1 == rhs) && (this->_2 == rhs);
			}

			Vector2<T> &operator=(const Vector2<T> &rhs) {
				this->_1 = rhs._1;
				this->_2 = rhs._2;
				return (*this);
			}
			Vector2<T> operator +(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 + rhs._1, this->_2 + rhs._2);
			}
			Vector2<T> operator -(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 - rhs._1, this->_2 - rhs._2);
			}
			Vector2<T> operator *(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 * rhs._1, this->_2 * rhs._2);
			}
			Vector2<T> operator /(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 / rhs._1, this->_2 / rhs._2);
			}
			Vector2<T> operator %(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 % rhs._1, this->_2 % rhs._2);
			}
			Vector2<T> operator ^(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 ^ rhs._1, this->_2 ^ rhs._2);
			}
			Vector2<T> operator &(const Vector2<T> &rhs) {
				return Vector2<T>(this->_1 & rhs._1, this->_2 & rhs._2);
			}
			operator bool() {
				return (this->_1 != 0.0f) && (this->_2 != 0.0f);
			}
			bool operator !() {
				return (this->_1 == 0.0f) && (this->_2 == 0.0f);
			}

			Vector2<T> &operator +=(const Vector2<T> &rhs) {
				this->_1 += rhs._1;
				this->_2 += rhs._2;
				return (*this);
			}
			Vector2<T> &operator -=(const Vector2<T> &rhs) {
				this->_1 -= rhs._1;
				this->_2 -= rhs._2;
				return (*this);
			}
			Vector2<T> &operator *=(const Vector2<T> &rhs) {
				this->_1 *= rhs._1;
				this->_2 *= rhs._2;
				return (*this);
			}
			Vector2<T> &operator /=(const Vector2<T> &rhs) {
				this->_1 /= rhs._1;
				this->_2 /= rhs._2;
				return (*this);
			}
			Vector2<T> &operator %=(const Vector2<T> &rhs) {
				this->_1 %= rhs._1;
				this->_2 %= rhs._2;
				return (*this);
			}
			Vector2<T> &operator ^=(const Vector2<T> &rhs) {
				this->_1 ^= rhs._1;
				this->_2 ^= rhs._2;
				return (*this);
			}
			Vector2<T> &operator &=(const Vector2<T> &rhs) {
				this->_1 &= rhs._1;
				this->_2 &= rhs._2;
				return (*this);
			}
			bool operator !=(const Vector2<T> &rhs) {
				return (this->_1 != rhs._1) || (this->_2 != rhs._2);
			}
			bool operator ==(const Vector2<T> &rhs) {
				return (this->_1 == rhs._1) && (this->_2 == rhs._2);
			}

			T &operator[](const int index) {
				switch (index) {
				case 0:
					return this->_1;
				case 1:
					return this->_2;
				}

				return this->_1;
			}

		public: // Functions
			virtual T distanceTo(const Vector2<T> &rhs) {
				Vector2<T> distance((this->_1 - rhs._1), (this->_2 - rhs._2));

				return (float)sqrt((distance.getX() * distance.getX()) +
					(distance.getY() * distance.getY()));
			}

		public: // Getters
			T getX() const {
				return this->_1;
			}
			T getY() const {
				return this->_2;
			}

			T *getXData() {
				return &this->_1;
			}
			T *getYData() {
				return &this->_2;
			}

		public: // Setters
			void setX(const T _1) {
				this->_1 = _1;
			}
			void setY(const T _2) {
				this->_2 = _2;
			}
		};
	}
}

#endif // VECTOR2_HPP