#ifndef CGAMEOFFSETHANDLER_HPP
#define CGAMEOFFSETHANDLER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>
#include <unordered_map>

#include "ISafeLogger.hpp"

namespace ando {
	namespace process_specific {
		class CGameOffsetHandler {
		private: // Variables
			::std::unique_ptr<::ando::logger::ISafeLogger> logger;
			::std::unordered_map<::std::string, ::std::uint64_t> offsetMap;

		public: // Constructors & Destructors
			CGameOffsetHandler();
			CGameOffsetHandler(::std::shared_ptr<::ando::logger::ILogger> logger);
			~CGameOffsetHandler();

		public: // Public Functions
			bool addOffset(::std::string name, ::std::uint64_t offset);
			::std::uint64_t getOffsetByName(::std::string name);
			::std::uint64_t getRelativeAddress(::std::uint64_t baseAddress, ::std::string name);
			::std::uint64_t getRelativeAddress(::std::string baseAddressName, ::std::string name);
		};
	}
}

#endif // CGAMEOFFSETHANDLER_HPP