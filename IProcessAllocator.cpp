#include "IProcessAllocator.hpp"

namespace ando {
	namespace memory {
		IProcessAllocator::IProcessAllocator(IProcess *process) {
			this->process = process;
		}

		MEM_PTR IProcessAllocator::alloc(::std::size_t size) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			if ((this->process == nullptr) || (this->process->getHandle() == INVALID_HANDLE_VALUE))
				return nullptr;

			return VirtualAllocEx(this->process->getHandle(), NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		}
		MEM_PTR IProcessAllocator::commit(MEM_PTR data, ::std::size_t size) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			if ((this->process == nullptr) || (this->process->getHandle() == INVALID_HANDLE_VALUE))
				return false;

			MEM_PTR address = this->alloc(size);

			if (address == nullptr)
				return nullptr;

			SIZE_T numberOfBytes = 0;

			if (WriteProcessMemory(this->process->getHandle(), address, data, size, &numberOfBytes) == 0) {
				this->free(address, size);

				return nullptr;
			}

			return address;
		}
		bool IProcessAllocator::free(MEM_PTR pointer, ::std::size_t size) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			if ((this->process == nullptr) || (this->process->getHandle() == INVALID_HANDLE_VALUE))
				return false;

			return VirtualFreeEx(this->process->getHandle(), pointer, size, MEM_RELEASE) == 1;
		}
	}
}