#include <Windows.h>

#include "IProcessHandler.hpp"

namespace ando {
	namespace memory {
		IProcessHandler::IProcessHandler(HANDLE processHandle) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			this->process = new IProcess(processHandle);
			this->reader = new IProcessReader(this->process);
			this->writer = new IProcessWriter(this->process);
			this->allocator = new IProcessAllocator(this->process);

			this->process->setId(NULL);
		}
		IProcessHandler::IProcessHandler(HWND windowHandle) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			this->process = new IProcess(INVALID_HANDLE_VALUE);
			this->reader = new IProcessReader(this->process);
			this->writer = new IProcessWriter(this->process);
			this->allocator = new IProcessAllocator(this->process);

			DWORD processId = 0;
			GetWindowThreadProcessId(windowHandle, &processId);

			this->process->setId(processId);
		}
		IProcessHandler::IProcessHandler(DWORD processId) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			this->process = new IProcess(INVALID_HANDLE_VALUE);
			this->reader = new IProcessReader(this->process);
			this->writer = new IProcessWriter(this->process);
			this->allocator = new IProcessAllocator(this->process);

			this->process->setId(processId);
		}
		IProcessHandler::IProcessHandler(::std::string processName) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			this->process = new IProcess(INVALID_HANDLE_VALUE);
			this->reader = new IProcessReader(this->process);
			this->writer = new IProcessWriter(this->process);
			this->allocator = new IProcessAllocator(this->process);

			this->process->setId(NULL);
			this->getProcess()->setExeName(processName);
		}
		IProcessHandler::~IProcessHandler() {
			std::lock_guard<std::mutex> lock(this->_mutex);

			for (auto it = this->modules.begin(); it != this->modules.end(); it++) {
				if (it->second)
					delete it->second;
			}

			this->modules.clear();

			delete this->allocator;
			delete this->writer;
			delete this->reader;
			delete this->process;
		}

		bool IProcessHandler::initialize() {
			std::lock_guard<std::mutex> lock(this->_mutex);

			if (this->getProcess()->getId() != NULL) {
				this->getProcess()->setHandle(OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->getProcess()->getId()));
			}
			else {
				this->enumarateProcesses([this](PROCESSENTRY32 *entry) {
					if (this->getProcess()->getExeName().compare(entry->szExeFile) != 0)
						return false;

					printf("Found Process: %s\n", entry->szExeFile);
					this->getProcess()->setId(entry->th32ProcessID);
					this->getProcess()->setHandle(OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry->th32ProcessID));
					return true;
				});
			}
			
			return this->enumarateModules([this](MODULEENTRY32 *entry) {
				if (entry == nullptr)
					return false;

				auto it = this->getModules().find(entry->szModule); 
				if ((it == this->getModules().end()) || (it->second == nullptr))
					return false;
				if (entry->szExePath == nullptr)
					return false;

				it->second->setFileName(entry->szExePath);
				it->second->setModuleName(entry->szModule);
				it->second->setBaseAddress((::std::ptrdiff_t)entry->hModule);
				it->second->setSize(entry->modBaseSize);
				it->second->setModuleId(entry->th32ModuleID);

				return false;
			});
		}

		IModule *IProcessHandler::addModuleToLoad(::std::string moduleName) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			auto module = new IModule();

			this->modules.insert(::std::pair<std::string, IModule *>(moduleName, module));

			return module;
		}
		IModule *IProcessHandler::getModuleByName(::std::string moduleName) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			auto it = this->getModules().find(moduleName);
			if (it == this->getModules().end())
				return nullptr;

			return it->second;
		}

		bool IProcessHandler::enumarateProcesses(::std::function<bool(PROCESSENTRY32 *entry)> func) {
			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
			if (snapshot == INVALID_HANDLE_VALUE) {
				printf("[IProcessHandler] Failed to get snapshot handle!\n");
				return false;
			}

			PROCESSENTRY32 entry;
			entry.dwSize = sizeof(PROCESSENTRY32);

			if (!Process32First(snapshot, &entry)) {
				printf("[IProcessHandler] Process32First failed!\n");
				CloseHandle(snapshot);
				return false;
			}

			do {
				if (func(&entry))
					break;
			} while (Process32Next(snapshot, &entry));

			CloseHandle(snapshot);
			return true;
		}

		bool IProcessHandler::enumarateModules(::std::function<bool(MODULEENTRY32 *entry)> func) {
			static std::mutex _mutex;
			std::lock_guard<std::mutex> lock(_mutex);

			if (this->getProcess()->getId() == NULL)
				return false;

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->getProcess()->getId());
			if (snapshot == INVALID_HANDLE_VALUE) {
				printf("[IProcessHandler] Failed to get snapshot handle!\n");
				return false;
			}
			
			MODULEENTRY32 entry;
			entry.dwSize = sizeof(MODULEENTRY32);

			if (!Module32First(snapshot, &entry)) {
				printf("[IProcessHandler] Process32First failed!\n");
				CloseHandle(snapshot);
				return false;
			}

			do {
				if (func(&entry))
					break;
			} while (Module32Next(snapshot, &entry));

			CloseHandle(snapshot);
			return true;
		}

		IProcess *IProcessHandler::getProcess() const {
			return this->process;
		}

		IProcessReader *IProcessHandler::getReader() const {
			return this->reader;
		}
		IProcessWriter *IProcessHandler::getWriter() const {
			return this->writer;
		}
		IProcessAllocator *IProcessHandler::getAllocator() const {
			return this->allocator;
		}
		std::map<std::string, IModule *> IProcessHandler::getModules() const {
			return this->modules;
		}
	}
}