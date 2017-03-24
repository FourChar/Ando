#ifndef IFILE_LOGGER_HPP
#define IFILE_LOGGER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <fstream>

#include "ILogger.hpp"

namespace ando {
	namespace logger {
		class IFileLogger : public ILogger {
		private:
			std::string logFile;
			std::ofstream fileStream;

		public:
			IFileLogger(::std::string logFile, bool useStandardStreams = false);
			IFileLogger(::std::string logFile, ELogLevel logLevel, bool useStandardStreams = false);

			~IFileLogger();

			virtual void rawLog(::std::string text);
		};
	}
}

#endif // IFILE_LOGGER_HPP