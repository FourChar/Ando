#ifndef CGLOBALOFFENSIVEBONEMANAGER_HPP
#define CGLOBALOFFENSIVEBONEMANAGER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <array>

#include "Matrix.hpp"
#include "Vector3.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				class CBoneManager {
				private:
					::std::array<::ando::math::Matrix<float, 3, 4>, 100> m_boneMatrixArray;

				public:
					CBoneManager() { }
					CBoneManager(const CBoneManager &rhs) {
						(*this) = rhs;
					}

					virtual ~CBoneManager() { }

				public:
					CBoneManager &operator=(const CBoneManager &rhs) {
						for (::std::size_t i = 0; i < this->m_boneMatrixArray.size(); i++) {
							this->m_boneMatrixArray.at(i) = rhs.m_boneMatrixArray.at(i);
						}
						return (*this);
					}

				public:
					::std::array<::ando::math::Matrix<float, 3, 4>, 100> &getBoneMatrixArray() {
						return this->m_boneMatrixArray;
					}

					::ando::math::Matrix<float, 3, 4> &getBoneMatrix(::std::size_t index) {
						return this->getBoneMatrixArray().at(index);
					}

					::ando::math::Vector3<float> getBoneOrigin(::std::size_t index) {
						auto boneMatrix = this->getBoneMatrix(index);

						::ando::math::Vector3<float> origin(boneMatrix[3], boneMatrix[7], boneMatrix[11]);
						return origin;
					}
				};
			}
		}
	}
}

#endif // CGLOBALOFFENSIVEBONEMANAGER_HPP