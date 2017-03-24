#ifndef MATRIX_HPP
#define MATRIX_HPP

#ifdef _MSC_VER
#pragma once
#endif

// TODO: Fix this class up
namespace ando {
	namespace math {
		template <typename T = float, ::std::size_t width = 4, ::std::size_t height = 4>
		class Matrix {
		private: // Variables
			T _data[width * height];

		public: // Constructors
			Matrix() {
				for (::std::size_t i = 0; i < (width * height); i++) {
					this->_data[i] = 0;
				}
			}
			Matrix(T _data[width * height]) {
				for (::std::size_t i = 0; i < (width * height); i++) {
					this->_data[i] = _data[i];
				}
			}

		public: // Operators
			Matrix<T> &operator=(const Matrix<T> &rhs) {
				for (::std::size_t i = 0; i < (width * height); i++) {
					this->_data[i] = rhs._data[i];
				}
				return (*this);
			}

			T &operator[](const ::std::size_t index) {
				return this->_data[index];
			}

		public: // Getters
			T get(int indexA, int indexB) const {
				return this->_data[indexA * indexB];
			}

			T *getData() {
				return &this->_data[0];
			}

		public: // Setters
			void set(int indexA, int indexB, const T value) {
				this->_data[indexA * indexB] = value;
			}
		};
	}
}

#endif // MATRIX_HPP
