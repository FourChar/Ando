#include <string>

#include "ELogLevel.hpp"

namespace ando {
	namespace logger {
		std::string logLevelToString(ELogLevel logLevel) {
			switch (logLevel) {
			case LOG_CRITICAL:
				return "CRITICAL";
			case LOG_ERROR:
				return "ERROR";
			case LOG_WARNING:
				return "WARNING";
			case LOG_DEBUG:
				return "DEBUG";
			case LOG_INFO:
				return "INFO";
			}

			return "";
		}
	}
}