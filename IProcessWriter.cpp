#include "IProcessWriter.hpp"

namespace ando {
	namespace memory {
		IProcessWriter::IProcessWriter(IProcess *process) {
			this->process = process;
		}

		bool IProcessWriter::writeByte(::std::uint64_t address, BYTE data) {
			return this->write(address, &data);
		}
		bool IProcessWriter::writeInt(::std::uint64_t address, int data) {
			return this->write(address, &data);
		}
		bool IProcessWriter::writeFloat(::std::uint64_t address, float data) {
			return this->write(address, &data);
		}
		bool IProcessWriter::writeLong(::std::uint64_t address, long data) {
			return this->write(address, &data);
		}
		bool IProcessWriter::writeString(::std::uint64_t address, ::std::string data) {
			return this->write(address, data.c_str(), data.size());
		}
	}
}