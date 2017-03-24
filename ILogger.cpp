#include <cstdarg>
#include <vector>
#include <iostream>

#include "ILogger.hpp"

namespace ando {
	namespace logger {
		ILogger::ILogger(bool useStandardStreams) {
			this->maxLogLevel = ELogLevel::LOG_INFO;
			this->useStandardStreams = useStandardStreams;
		}
		ILogger::ILogger(ELogLevel maxLogLevel, bool useStandardStreams) {
			this->maxLogLevel = maxLogLevel;
			this->useStandardStreams = useStandardStreams;
		}

		void ILogger::log(::std::string format, ...) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			if (format.empty())
				return;

			format = ::std::string("[") + logLevelToString(this->getMaxLogLevel()) + ::std::string("] ") + format;

			std::vector<char> buffer(256);

			va_list args;
			va_start(args, format);
			vsnprintf_s(&buffer[0], buffer.size(), buffer.size() + strlen(format.c_str()), format.c_str(), args);
			va_end(args);

			std::string bufferStr(&buffer[0]);

			this->log(ELogLevel::LOG_INFO, bufferStr);
		}

		void ILogger::log(ELogLevel logLevel, ::std::string format, ...) {
			std::lock_guard<std::mutex> lock(this->_mutex);

			if (format.empty())
				return;
			if (logLevel < this->getMaxLogLevel())
				return;

			format = ::std::string("[") + logLevelToString(logLevel) + ::std::string("] ") + format;

			std::vector<char> buffer(256);

			va_list args;
			va_start(args, format);
			vsnprintf_s(&buffer[0], buffer.size(), buffer.size() + strlen(format.c_str()), format.c_str(), args);
			va_end(args);

			std::string bufferStr(&buffer[0]);

			this->rawLog(bufferStr);

			if (!this->mustUseStandardStreams())
				return;

			switch (logLevel) {
				case LOG_CRITICAL:
				case LOG_ERROR:
					std::cerr << bufferStr << ::std::endl;
					break;

				case LOG_WARNING:
				case LOG_DEBUG:
				case LOG_INFO:
					std::cout << bufferStr << ::std::endl;
					break;
			}
		}

		ELogLevel ILogger::getMaxLogLevel() const {
			return this->maxLogLevel;
		}

		bool ILogger::mustUseStandardStreams() const {
			return this->useStandardStreams;
		}
	}
}