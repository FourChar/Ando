#ifndef IBASEPROCESSINSTANCE_HPP
#define IBASEPROCESSINSTANCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <thread>
#include <mutex>
#include <vector>

#define ANDO_PROCESS_INSTANCE_WAIT_FOR_START_MILLS		125
#define ANDO_PROCESS_INSTANCE_WAIT_FOR_END_MILLS		250
#define ANDO_PROCESS_INSTANCE_UPDATE_MILLS				5

#include "IBaseAndoEntity.hpp"

#include "ISafeLogger.hpp"
#include "IProcessHandler.hpp"

namespace ando {
	namespace process_specific {
		class IBaseProcessInstance {
		private: // Variables
			bool updatesStarted;
			bool runUpdater;
			::std::mutex _mutex;
			::std::unique_ptr<::std::thread> updateThread;

			::std::shared_ptr<::ando::logger::ISafeLogger> logger;
			::std::shared_ptr<::ando::memory::IProcessHandler> processHandler;

		public: // Constructors & Destructors
			IBaseProcessInstance(::std::shared_ptr<::ando::logger::ILogger> logger, ::std::shared_ptr<::ando::memory::IProcessHandler> processHandler);
			IBaseProcessInstance(::std::shared_ptr<::ando::memory::IProcessHandler> processHandler);
			IBaseProcessInstance();

			virtual ~IBaseProcessInstance();

		protected: // Protected Functions
			virtual void processUpdate() = 0;

			void safeProcessUpdate();

		public: // Public Getters
			bool shouldRunUpdater();

		public: // Public Setters
			void setShouldRunUpdater(const bool runUpdater);

			void setLogger(::std::shared_ptr<::ando::logger::ILogger> logger);
			void setProcessHandler(::std::shared_ptr<::ando::memory::IProcessHandler> processHandler);

		protected: // Protected Getters
			::std::mutex &getMutex();

			::std::shared_ptr<::ando::logger::ISafeLogger> &getLogger();
			::std::shared_ptr<::ando::memory::IProcessHandler> &getProcessHandler();

			bool hasProcessHandler();

			bool haveUpdatesStarted();

		protected: // Protected Setters
			void setHaveUpdatesStarted(const bool updatesStarted);
		};
	}
}

#endif // IBASEPROCESSINSTANCE_HPP