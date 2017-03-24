#ifndef IMODULE_HANDLER_HPP
#define IMODULE_HANDLER_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace ando {
	namespace memory {
		class IModule {
		private:
			DWORD moduleId;
			std::string fileName;
			std::string moduleName;
			std::ptrdiff_t baseAddress;
			std::size_t size;

		public:
			DWORD getModuleId() { return this->moduleId; }
			std::string getFileName() { return this->fileName; }
			std::string getModuleName() { return this->moduleName; }
			std::ptrdiff_t getBaseAddress() { return this->baseAddress; }
			std::size_t getSize() { return this->size; }

			void setModuleId(DWORD moduleId) { this->moduleId = moduleId; }
			void setFileName(::std::string fileName) { this->fileName = fileName; }
			void setModuleName(::std::string moduleName) { this->moduleName = moduleName; }
			void setBaseAddress(::std::ptrdiff_t baseAddress) { this->baseAddress = baseAddress; }
			void setSize(::std::size_t size) { this->size = size; }
		};
	}
}

#endif // IMODULE_HANDLER_HPP