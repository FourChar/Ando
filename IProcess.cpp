#include "IProcess.hpp"

namespace ando {
	namespace memory {
		IProcess::IProcess() {
			this->handle = (MEM_PTR)-1;
			this->exeName = "";
		}

		IProcess::IProcess(MEM_PTR handle) {
			this->handle = handle;
			this->exeName = "";
		}

		MEM_PTR IProcess::getHandle() const {
			return this->handle;
		}

		unsigned long IProcess::getId() const {
			return this->processId;
		}

		std::string IProcess::getExeName() const {
			return this->exeName;
		}

		void IProcess::setHandle(MEM_PTR handle) {
			this->handle = handle;
		}

		void IProcess::setId(unsigned long processId) {
			this->processId = processId;
		}

		void IProcess::setExeName(::std::string exeName) {
			this->exeName = exeName;
		}
	}
}