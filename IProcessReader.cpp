#include "IProcessReader.hpp"

namespace ando {
	namespace memory {
		IProcessReader::IProcessReader(IProcess *process) {
			this->process = process;
		}

		BYTE IProcessReader::readByte(::std::uint64_t address) {
			BYTE data = 0;

			if (!this->read<BYTE>(address, &data))
				return 0;

			return data;
		}
		bool IProcessReader::readBool(::std::uint64_t address) {
			bool data = false;

			if (!this->read<bool>(address, &data))
				return false;

			return data;
		}
		int IProcessReader::readInt(::std::uint64_t address) {
			int data = 0;

			if (!this->read(address, &data))
				return 0;

			return data;
		}
		float IProcessReader::readFloat(::std::uint64_t address) {
			float data = 0;

			if (!this->read(address, &data))
				return 0;

			return data;
		}
		long IProcessReader::readLong(::std::uint64_t address) {
			long data = 0;

			if (!this->read(address, &data))
				return 0;

			return data;
		}
		::std::string IProcessReader::readString(::std::uint64_t address) {
			char buffer[256] = { 0 };

			if (!this->read(address, &buffer))
				return "";

			::std::string data;
			for (::std::size_t i = 0; i < sizeof(buffer); i++) {
				if (buffer[i] == '\0')
					break;

				data += buffer[i];
			}

			return data;
		}
	}
}