#ifndef ELOGLEVEL_HPP
#define ELOGLEVEL_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace ando {
	namespace logger {
		enum ELogLevel {
			LOG_CRITICAL,
			LOG_ERROR,
			LOG_WARNING,
			LOG_DEBUG,
			LOG_INFO,

			LOG_NONE
		};

		std::string logLevelToString(ELogLevel logLevel);
	}
}

#endif // ELOGLEVEL_HPP