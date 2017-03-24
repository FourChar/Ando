#ifndef ISAFELOGGER_HPP
#define ISAFELOGGER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>
#include <string>

#include "ILogger.hpp"
#include "ELogLevel.hpp"

namespace ando {
	namespace logger {
		class ISafeLogger {
		private: // Variables
			::std::shared_ptr<::ando::logger::ILogger> logger;

		public: // Constructors
			ISafeLogger();
			ISafeLogger(::std::shared_ptr<::ando::logger::ILogger> logger);

		public: // Public Functions
			void log(::std::string format, ...);
			void log(::ando::logger::ELogLevel logLevel, ::std::string format, ...);

		protected: // Protected Functions
			bool hasLogger() const;

		protected: // Protected Getters
			::std::shared_ptr<::ando::logger::ILogger> &getLogger();

		public: // Public Setters
			void setLogger(::std::shared_ptr<::ando::logger::ILogger> logger);
		};
	}
}

#endif // ISAFELOGGER_HPP