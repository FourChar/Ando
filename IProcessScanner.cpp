#include "IProcessScanner.hpp"

namespace ando {
	namespace memory {
		// Constructors & Destructors
		IProcessScanner::IProcessScanner() {
			this->processHandler = nullptr;
		}
		IProcessScanner::IProcessScanner(::std::shared_ptr<::ando::memory::CProcessHandler> processHandler) {
			this->processHandler = processHandler;
		}

		// Public Functions
		::std::uintptr_t IProcessScanner::findPatternEx(::std::string moduleName, char *pattern) {
			auto module = this->getProcessHandler()->getModuleByName(moduleName);
			if (!module)
				return 0;

			::std::uintptr_t start = module->getBaseAddress();
			::std::uintptr_t end = start + module->getSize();

			::std::uintptr_t chunk = start;
			::std::size_t bytesRead = 0;

			while (chunk < end) {
				if (!this->read(chunk, 4096))
					return 0;

				auto internalAddress = IProcessScanner::findPattern((PBYTE)this->getBuffer(), this->getBufferSize(), pattern);
				if (internalAddress != nullptr) {
					::std::uintptr_t offsetFromBuffer = ((::std::uintptr_t)internalAddress) - ((::std::uintptr_t)this->getBuffer());
					return (chunk + offsetFromBuffer);
				}

				chunk += bytesRead;
			}

			return 0;
		}

		PBYTE IProcessScanner::findPattern(PBYTE baseAddress, ::std::size_t size, char *pattern) {
			BYTE start = pattern[0];
			PBYTE end = baseAddress + size - strlen(pattern);

			for (; baseAddress < end; ++baseAddress) {
				if ((*baseAddress) != start)
					continue;

				if (IProcessScanner::compareByteArray(baseAddress, pattern))
					return baseAddress;
			}

			return nullptr;
		}

		bool IProcessScanner::compareByteArray(PBYTE baseAddress, char *pattern) {
			for (; (*pattern); ++pattern, ++baseAddress) {
				if ((*pattern) == '\x00')
					continue;

				if ((*pattern) != (*baseAddress))
					return false;
			}

			return true;
		}

		// Private Functions
		char *IProcessScanner::createBuffer(::std::size_t size) {
			if (size <= 0)
				return nullptr;

			return (new char[size]);
		}
		bool IProcessScanner::releaseBuffer(char *buffer) {
			if (buffer == nullptr)
				return false;

			delete[] buffer;
			buffer = nullptr;
			return true;
		}

		bool IProcessScanner::localBufferExists() {
			return (this->buffer != nullptr);
		}
		bool IProcessScanner::releaseLocalBuffer() {
			return IProcessScanner::releaseBuffer(this->getBuffer());
		}
		bool IProcessScanner::resizeLocalBuffer(::std::size_t size) {
			if (!this->localBufferExists())
				return false;

			if (this->getBufferSize() == size) {
				this->emptyLocalBuffer();
				return true;
			}

			auto tempBuffer = IProcessScanner::createBuffer(size);
			for (::std::size_t i = 0; i < min(this->getBufferSize(), size); i++)
				tempBuffer[i] = this->getBuffer()[i];
			
			if (!this->releaseLocalBuffer())
				return false;

			this->setBuffer(tempBuffer);
			this->setBufferSize(size);
			return true;
		}
		bool IProcessScanner::emptyLocalBuffer() {
			if (!this->localBufferExists())
				return false;

			for (::std::size_t i = 0; i < this->getBufferSize(); i++)
				this->getBuffer()[i] = 0;
			
			return true;
		}
		bool IProcessScanner::prepareLocalBuffer(::std::size_t size) {
			if (this->resizeLocalBuffer(size))
				return true;

			if (!this->releaseLocalBuffer())
				return false;

			auto buffer = IProcessScanner::createBuffer(size);
			if (buffer == nullptr)
				return false;

			if (!this->emptyLocalBuffer())
				return false;

			this->setBuffer(buffer);
			this->setBufferSize(size);
			return true;
		}

		bool IProcessScanner::read(::std::uintptr_t baseAddress, ::std::size_t size, ::std::size_t *bytesRead) {
			if ((baseAddress < 0) || (size <= 0))
				return false;

			if (!this->prepareLocalBuffer(size))
				return false;

			if (!this->getProcessHandler()->getReader()->read<char *>(baseAddress, &this->getBuffer(), size))
				return false;

			(*bytesRead) = size;
			return true;
		}
		
		// Public Setters
		void IProcessScanner::setProcessHandler(::std::shared_ptr<::ando::memory::CProcessHandler> processHandler) {
			this->processHandler = processHandler;
		}

		// Private Getters
		::std::shared_ptr<::ando::memory::CProcessHandler> IProcessScanner::getProcessHandler() {
			return this->processHandler;
		}
		char *&IProcessScanner::getBuffer() {
			return this->buffer;
		}
		::std::size_t IProcessScanner::getBufferSize() const {
			return this->size;
		}

		// Private Setters
		void IProcessScanner::setBuffer(char *buffer) {
			this->buffer = buffer;
		}
		void IProcessScanner::setBufferSize(::std::size_t size) {
			this->size = size;
		}
	}
}