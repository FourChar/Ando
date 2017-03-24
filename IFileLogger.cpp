#include "IFileLogger.hpp"

namespace ando {
	namespace logger {
		IFileLogger::IFileLogger(::std::string logFile, bool useStandardStreams) : ILogger(useStandardStreams) {
			this->logFile = logFile;
			this->fileStream.open(logFile.c_str(), ::std::ios::trunc | ::std::ios::out);
		}
		IFileLogger::IFileLogger(::std::string logFile, ELogLevel logLevel, bool useStandardStreams) : ILogger(logLevel, useStandardStreams) {
			this->logFile = logFile;
			this->fileStream.open(logFile.c_str());
		}

		IFileLogger::~IFileLogger() {
			this->fileStream.flush();
			this->fileStream.close();
		}

		void IFileLogger::rawLog(::std::string text) {
			this->fileStream << text << ::std::endl;
			this->fileStream.flush();
		}
	}
}