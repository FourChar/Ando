#ifndef IPROCESS_ALLOCATOR_HPP
#define IPROCESS_ALLOCATOR_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <Windows.h>
#include <memory>
#include <mutex>

#include "IProcess.hpp"

namespace ando {
	namespace memory {
		class IProcessAllocator {
		private:
			std::mutex _mutex;

			IProcess *process;

		public:
			IProcessAllocator(IProcess *process);

		public:
			MEM_PTR alloc(::std::size_t size);
			MEM_PTR commit(MEM_PTR data, ::std::size_t size);
			bool free(MEM_PTR pointer, ::std::size_t size);
		};
	}
}

#endif // IPROCESS_ALLOCATOR_HPP