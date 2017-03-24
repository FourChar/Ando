#ifndef IBASIC_LOGGER_HPP
#define IBASIC_LOGGER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <fstream>

namespace ando {
	namespace logger {
		class IBasicLogger {
		public:
			virtual void rawLog(::std::string text) = 0;
		};
	}
}

#endif // IBASIC_LOGGER_HPP