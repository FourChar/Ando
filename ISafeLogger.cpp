#include <cstdarg>
#include <vector>

#include "ISafeLogger.hpp"

namespace ando {
	namespace logger {
		// Constructors
		ISafeLogger::ISafeLogger() { }
		ISafeLogger::ISafeLogger(::std::shared_ptr<::ando::logger::ILogger> logger) : logger(logger) { }

		// Public Functions
		void ISafeLogger::log(::std::string format, ...) {
			if (!this->hasLogger() || format.empty())
				return;

			std::vector<char> buffer(256);

			va_list args;
			va_start(args, format);
			vsnprintf_s(&buffer[0], buffer.size(), buffer.size() + strlen(format.c_str()), format.c_str(), args);
			va_end(args);

			std::string bufferStr(&buffer[0]);

			this->getLogger()->log(::ando::logger::ELogLevel::LOG_INFO, bufferStr);
		}
		void ISafeLogger::log(::ando::logger::ELogLevel logLevel, ::std::string format, ...) {
			if (!this->hasLogger() || format.empty())
				return;

			std::vector<char> buffer(256);
			
			va_list args;
			va_start(args, format);
			vsnprintf_s(&buffer[0], buffer.size(), buffer.size() + strlen(format.c_str()), format.c_str(), args);
			va_end(args);

			std::string bufferStr(&buffer[0]);

			this->getLogger()->log(logLevel, bufferStr);
		}
		
		// Protected Functions
		bool ISafeLogger::hasLogger() const {
			return (this->logger != nullptr);
		}
		
		// Protected Getters
		::std::shared_ptr<::ando::logger::ILogger> &ISafeLogger::getLogger() {
			return this->logger;
		}

		// Public Setters
		void ISafeLogger::setLogger(::std::shared_ptr<::ando::logger::ILogger> logger) {
			this->logger = logger;
		}
	}
}