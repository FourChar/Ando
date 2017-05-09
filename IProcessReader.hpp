#ifndef IPROCESS_READER_HPP
#define IPROCESS_READER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <Windows.h>
#include <string>
#include <memory>
#include <mutex>

#include "IProcess.hpp"

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix.hpp"

namespace ando {
	namespace memory {
		class IProcessReader {
		private:
			std::mutex _mutex;

			IProcess *process;

		public:
			IProcessReader(IProcess * process);

		public:
			BYTE readByte(::std::uintptr_t address);
			bool readBool(::std::uintptr_t address);
			int readInt(::std::uintptr_t address);
			float readFloat(::std::uintptr_t address);
			long readLong(::std::uintptr_t address);
			::std::string readString(::std::uintptr_t address);

			template <typename T>
			math::Vector2<T> readVector2(::std::uintptr_t address) {
				static math::Vector2<T> vector;

				if (!this->read(address, vector.getXData(), 2 * sizeof(T)))
					return vector;

				return vector;
			}

			template <typename T>
			math::Vector3<T> readVector3(::std::uintptr_t address) {
				static math::Vector3<T> vector;

				if (!this->read(address, vector.getXData(), 3 * sizeof(T)))
					return vector;

				return vector;
			}

			template <typename T>
			math::Vector4<T> readVector4(::std::uintptr_t address) {
				static math::Vector4<T> vector;

				if (!this->read(address, vector.getXData(), (4 + 1) * sizeof(T)))
					return vector;

				return vector;
			}

			template <typename T, ::std::size_t width, ::std::size_t height>
			math::Matrix<T, width, height> readMatrix(::std::uintptr_t address) {
				static math::Matrix<T, width, height> matrix;

				if (!this->read(address, &matrix, width * height * sizeof(T)))
					return matrix;

				return matrix;
			}

			template <typename T>
			bool read(::std::uintptr_t address, T *data, ::std::size_t size = sizeof(T), ::std::size_t *bytesRead = nullptr) {
				std::lock_guard<std::mutex> lock(this->_mutex);

				if ((this->process == nullptr) || (this->process->getHandle() == (MEM_PTR)-1))
					return false;

				::std::size_t numberOfBytes = 0;
				if (ReadProcessMemory(this->process->getHandle(), (LPCVOID)address, (LPVOID)data, (SIZE_T)size, reinterpret_cast<SIZE_T *>((bytesRead == nullptr) ? &numberOfBytes : bytesRead)) == 0)
					return false;

				return (numberOfBytes == size);
			}
		};
	}
}

#endif // IPROCESS_READER_HPP