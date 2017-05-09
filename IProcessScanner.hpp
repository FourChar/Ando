#ifndef IPROCESSSCANNER_HPP
#define IPROCESSSCANNER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>

#include "CProcessHandler.hpp"

namespace ando {
	namespace memory {
		class IProcessScanner {
		private: // Variables
			::std::shared_ptr<::ando::memory::CProcessHandler> processHandler;
			char *buffer;
			::std::size_t size;

		public: // Constructors & Destructors
			IProcessScanner();
			IProcessScanner(::std::shared_ptr<::ando::memory::CProcessHandler> processHandler);

		public: // Public Functions
			::std::uintptr_t findPatternEx(::std::string moduleName, char *pattern);

		private: // Private Functions
			static PBYTE findPattern(PBYTE base, ::std::size_t size, char *pattern);
			static bool compareByteArray(PBYTE baseAddress, char *pattern);

			static char *createBuffer(::std::size_t size);
			static bool releaseBuffer(char *buffer);

			bool localBufferExists();
			bool releaseLocalBuffer();
			bool resizeLocalBuffer(::std::size_t size);
			bool emptyLocalBuffer();
			bool prepareLocalBuffer(::std::size_t size);

			bool read(::std::uintptr_t baseAddress, ::std::size_t size, ::std::size_t *bytesRead = nullptr);

		public: // Public Getters

		public: // Public Setters
			void setProcessHandler(::std::shared_ptr<::ando::memory::CProcessHandler> processHandler);

		private: // Private Getters
			::std::shared_ptr<::ando::memory::CProcessHandler> getProcessHandler();
			char *&getBuffer();
			::std::size_t getBufferSize() const;

		private: // Private Setters
			void setBuffer(char *buffer);
			void IProcessScanner::setBufferSize(::std::size_t size);
		};
	}
}

#endif