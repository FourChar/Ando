#ifndef MEMORY_BLOCK_HPP
#define MEMORY_BLOCK_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>

#include "IProcessHandler.hpp"

namespace ando {
	namespace memory {
		class MemoryBlock {
		private:
			std::mutex _mutex;

			std::shared_ptr<IProcessHandler> processHandler;
			std::uint64_t baseAddress;
			std::uint64_t size;
			std::uint64_t offset;
			char *data;

		public:
			MemoryBlock(::std::shared_ptr<IProcessHandler> processHandler, ::std::uint64_t baseAddress, ::std::uint64_t size, ::std::uint64_t offset = 0) {
				if ((baseAddress == 0) || (size == 0))
					return;

				this->processHandler = processHandler;
				this->baseAddress = baseAddress;
				this->size = size;
				this->offset = offset;
				this->data = new char[(::std::uint32_t)this->getSize()];
			}
			~MemoryBlock() {
				if (this->getData() != nullptr)
					delete[] this->data;
			}

		private:
			bool readSection(::std::uint64_t baseAddress, ::std::uint64_t size) {
				return this->processHandler->getReader()->read(baseAddress, this->getData(), (::std::size_t)size);
			}

		public:
			bool readSection() {
				std::lock_guard<std::mutex> lock(this->_mutex);

				if (this->getData() == nullptr)
					return false;
				if ((this->getBaseAddress() == 0) || (this->getSize() == 0))
					return false;

				return this->readSection(this->getBaseAddress() + this->getOffset(), this->getSize());
			}

			template <typename T>
			bool getAt(::std::uint64_t offset, T *dataPtr, ::std::uint64_t copySize = sizeof(T)) {
				std::lock_guard<std::mutex> lock(this->_mutex);

				if (dataPtr == nullptr)
					return false;
				if (this->getData() == nullptr)
					return false;
				if ((this->getBaseAddress() == 0) || (this->getSize() == 0))
					return false;
				if (((offset - this->getOffset()) == 0) || (((offset - this->getOffset()) + copySize) > this->getSize()))
					return false;

				auto dataAt = this->getDataAt(offset - this->getOffset());
				for (::std::size_t i = 0; i < copySize; i++)
					reinterpret_cast<char *>(dataPtr)[i] = dataAt[i];

				return true;
			}

		public:
			std::uint64_t getBaseAddress() const {
				return this->baseAddress;
			}
			std::uint64_t getSize() const {
				return this->size;
			}
			std::uint64_t getOffset() const {
				return this->offset;
			}
			const char *getData() const {
				return this->data;
			}
			const char *getDataAt(::std::uint64_t offset) const {
				return (const char *)(((::std::uint64_t)this->getData()) + offset);
			}
		};
	}
}

#endif // MEMORY_BLOCK_HPP