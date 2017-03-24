#ifndef IPROCESS_HANDLER_HPP
#define IPROCESS_HANDLER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <memory>
#include <map>

#include "ILogger.hpp"
#include "IModule.hpp"
#include "IProcess.hpp"
#include "IProcessReader.hpp"
#include "IProcessWriter.hpp"
#include "IProcessAllocator.hpp"

namespace ando {
	namespace memory {
		class IProcessHandler {
		private:
			std::mutex _mutex;

			ando::memory::IProcess *process;
			ando::memory::IProcessReader *reader;
			ando::memory::IProcessWriter *writer;
			ando::memory::IProcessAllocator *allocator;

			std::map<std::string, IModule *> modules;

		public:
			IProcessHandler(HANDLE processHandle);
			IProcessHandler(HWND windowHandle);
			IProcessHandler(DWORD processId);
			IProcessHandler(::std::string processName);
			~IProcessHandler();

			bool initialize();

		public:
			IModule *addModuleToLoad(::std::string moduleName);
			IModule *getModuleByName(::std::string moduleName);

		private:
			bool enumarateProcesses(::std::function<bool(PROCESSENTRY32 *entry)> func);
			bool enumarateModules(::std::function<bool(MODULEENTRY32 *entry)> func);

		public:
			ando::memory::IProcess *getProcess() const;
			ando::memory::IProcessReader *getReader() const;
			ando::memory::IProcessWriter *getWriter() const;
			ando::memory::IProcessAllocator *getAllocator() const;
			std::map<std::string, IModule *> getModules() const;
		};
	}
}

#endif // IPROCESS_HANDLER_HPP