#include "CGameOffsetHandler.hpp"

namespace ando {
	namespace process_specific {
		CGameOffsetHandler::CGameOffsetHandler() {
			this->logger = ::std::make_unique<::ando::logger::ISafeLogger>();
		}
		CGameOffsetHandler::CGameOffsetHandler(::std::shared_ptr<::ando::logger::ILogger> logger) {
			this->logger = ::std::make_unique<::ando::logger::ISafeLogger>(logger);
		}
		CGameOffsetHandler::~CGameOffsetHandler() { }

		bool CGameOffsetHandler::addOffset(::std::string name, ::std::uint64_t offset) {
			auto it = this->offsetMap.find(name);
			if (it != this->offsetMap.end())
				return false;

			this->logger->log(::ando::logger::ELogLevel::LOG_DEBUG, "{CGameOffsetHandler::addOffset} Added new Offset: (%s, 0x%.8X)", name.c_str(), offset);

			this->offsetMap.emplace(name, offset);
			return true;
		}

		::std::uint64_t CGameOffsetHandler::getOffsetByName(::std::string name) {
			auto it = this->offsetMap.find(name);
			if (it == this->offsetMap.end())
				return 0;

			return it->second;
		}

		::std::uint64_t CGameOffsetHandler::getRelativeAddress(::std::uint64_t baseAddress, ::std::string name) {
			return (baseAddress + this->getOffsetByName(name));
		}

		::std::uint64_t CGameOffsetHandler::getRelativeAddress(::std::string baseAddressName, ::std::string name) {
			return (this->getOffsetByName(baseAddressName) + this->getOffsetByName(name));
		}
	}
}