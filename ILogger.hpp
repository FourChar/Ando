#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <mutex>
#include <string>

#include "IBasicLogger.hpp"
#include "ELogLevel.hpp"

namespace ando {
	namespace logger {
		class ILogger : public IBasicLogger {
		private: // Variables
			std::mutex _mutex;
			ELogLevel maxLogLevel;
			bool useStandardStreams;

		public: // Constructors
			ILogger(bool useStandardStreams = false);
			ILogger(ELogLevel maxLogLevel, bool useStandardStreams = false);

		public: // Public Functions
			virtual void log(::std::string format, ...);
			virtual void log(ELogLevel logLevel, ::std::string format, ...);

		protected: // Protected Getters
			ELogLevel getMaxLogLevel() const;
			bool mustUseStandardStreams() const;
		};
	}
}

#endif // ILOGGER_HPP