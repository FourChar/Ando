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
			BYTE readByte(::std::uint64_t address);
			bool readBool(::std::uint64_t address);
			int readInt(::std::uint64_t address);
			float readFloat(::std::uint64_t address);
			long readLong(::std::uint64_t address);
			::std::string readString(::std::uint64_t address);

			template <typename T>
			math::Vector2<T> readVector2(::std::uint64_t address) {
				static math::Vector2<T> vector;

				if (!this->read(address, vector.getXData(), 2 * sizeof(T)))
					return vector;

				return vector;
			}

			template <typename T>
			math::Vector3<T> readVector3(::std::uint64_t address) {
				static math::Vector3<T> vector;

				if (!this->read(address, vector.getXData(), 3 * sizeof(T)))
					return vector;

				return vector;
			}

			template <typename T>
			math::Vector4<T> readVector4(::std::uint64_t address) {
				static math::Vector4<T> vector;

				if (!this->read(address, vector.getXData(), (4 + 1) * sizeof(T)))
					return vector;

				return vector;
			}

			template <typename T, ::std::size_t width, ::std::size_t height>
			math::Matrix<T, width, height> readMatrix(::std::uint64_t address) {
				static math::Matrix<T, width, height> matrix;

				if (!this->read(address, &matrix, width * height * sizeof(T)))
					return matrix;

				return matrix;
			}

			template <typename T>
			bool read(::std::uint64_t address, T *data, ::std::size_t size = sizeof(T)) {
				std::lock_guard<std::mutex> lock(this->_mutex);

				if ((this->process == nullptr) || (this->process->getHandle() == (MEM_PTR)-1))
					return false;

				::std::size_t numberOfBytes = 0;
				if (ReadProcessMemory(this->process->getHandle(), (LPCVOID)address, (LPVOID)data, (SIZE_T)size, reinterpret_cast<SIZE_T *>(&numberOfBytes)) == 0)
					return false;

				return (numberOfBytes == size);
			}
		};
	}
}

#endif // IPROCESS_READER_HPP