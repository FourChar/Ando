#ifndef IPROCESS_WRITER_HPP
#define IPROCESS_WRITER_HPP

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
		class IProcessWriter {
		private:
			std::mutex _mutex;

			IProcess *process;

		public:
			IProcessWriter(IProcess *process);

		public:
			bool writeByte(::std::uintptr_t address, BYTE data);
			bool writeInt(::std::uintptr_t address, int data);
			bool writeFloat(::std::uintptr_t address, float data);
			bool writeLong(::std::uintptr_t address, long data);
			bool writeString(::std::uintptr_t address, ::std::string data);

			template <typename T>
			bool writeVector2(::std::uintptr_t address, const math::Vector2<T> data) {
				return this->write(address, data.getXData(), (2 + 1) * sizeof(T));
			}

			template <typename T>
			bool writeVector3(::std::uintptr_t address, const math::Vector3<T> data) {
				return this->write(address, data.getXData(), (3 + 1) * sizeof(T));
			}

			template <typename T>
			bool writeVector4(::std::uintptr_t address, const math::Vector4<T> data) {
				return this->write(address, data.getXData(), (4 + 1) * sizeof(T));
			}

			template <typename T, ::std::size_t width, ::std::size_t height>
			bool writeMatrix(::std::uintptr_t address, const math::Matrix<T, width, height> data) {
				return this->write(address, data.getData(), width * height * sizeof(T));
			}

			template <typename T>
			bool write(::std::uintptr_t address, const T *data, ::std::size_t size = sizeof(T)) {
				std::lock_guard<std::mutex> lock(this->_mutex);

				if ((this->process == nullptr) || (this->process->getHandle() == INVALID_HANDLE_VALUE))
					return false;

				::std::uintptr_t numberOfBytes = 0;
				if (!WriteProcessMemory(this->process->getHandle(), (LPVOID)address, (LPCVOID)data, size, reinterpret_cast<SIZE_T *>(&numberOfBytes)))
					return false;

				return (numberOfBytes == size);
			}
		};
	}
}

#endif // IPROCESS_WRITER_HPP