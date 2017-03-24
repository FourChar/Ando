#ifndef IPROCESS_HPP
#define IPROCESS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <memory>

namespace ando {
	namespace memory {
		typedef void* MEM_PTR;

		class IProcess {
		private:
			MEM_PTR handle;
			unsigned long processId;
			std::string exeName;

		public:
			IProcess();
			IProcess(MEM_PTR handle);

		public:
			MEM_PTR getHandle() const;
			unsigned long getId() const;
			std::string getExeName() const;

		public:
			void setHandle(MEM_PTR handle);
			void setId(unsigned long processId);
			void setExeName(::std::string exeName);
		};
	}
}

#endif // IPROCESS_HPP