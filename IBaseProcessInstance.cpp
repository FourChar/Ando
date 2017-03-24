#include "IBaseProcessInstance.hpp"

namespace ando {
	namespace process_specific {
		// Constructors & Destructors
		IBaseProcessInstance::IBaseProcessInstance(::std::shared_ptr<::ando::logger::ILogger> logger, ::std::shared_ptr<::ando::memory::IProcessHandler> processHandler) {
			this->logger = ::std::make_shared<::ando::logger::ISafeLogger>(logger);
			this->processHandler = processHandler;
			this->updatesStarted = false;
			this->runUpdater = false;
			this->updateThread = ::std::make_unique<::std::thread>(::std::bind(&IBaseProcessInstance::safeProcessUpdate, this));
		}
		IBaseProcessInstance::IBaseProcessInstance(::std::shared_ptr<::ando::memory::IProcessHandler> processHandler) {
			this->logger = ::std::make_shared<::ando::logger::ISafeLogger>();
			this->processHandler = processHandler;
			this->updatesStarted = false;
			this->runUpdater = false;
			this->updateThread = ::std::make_unique<::std::thread>(::std::bind(&IBaseProcessInstance::safeProcessUpdate, this));
		}
		IBaseProcessInstance::IBaseProcessInstance() {
			this->logger = ::std::make_shared<::ando::logger::ISafeLogger>();
			this->processHandler = nullptr;
			this->updatesStarted = false;
			this->runUpdater = false;
			this->updateThread = ::std::make_unique<::std::thread>(::std::bind(&IBaseProcessInstance::safeProcessUpdate, this));
		}

		IBaseProcessInstance::~IBaseProcessInstance() {
			while (!this->haveUpdatesStarted()) {
				this->setShouldRunUpdater(true);
				::std::this_thread::sleep_for(::std::chrono::milliseconds(ANDO_PROCESS_INSTANCE_WAIT_FOR_END_MILLS));
			}

			this->setShouldRunUpdater(false);

			if (this->updateThread->joinable())
				this->updateThread->join();
		}

		// Protected Functions
		void IBaseProcessInstance::safeProcessUpdate() {
			this->setHaveUpdatesStarted(false);

			while (!this->shouldRunUpdater()) {
				::std::this_thread::sleep_for(::std::chrono::milliseconds(ANDO_PROCESS_INSTANCE_WAIT_FOR_START_MILLS));
			}

			this->setHaveUpdatesStarted(true);

			while (this->shouldRunUpdater()) {
				this->processUpdate();

				::std::this_thread::sleep_for(::std::chrono::milliseconds(ANDO_PROCESS_INSTANCE_UPDATE_MILLS));
			}
		}

		// Public Getters
		bool IBaseProcessInstance::shouldRunUpdater() {
			this->getMutex().lock();
			bool result = this->runUpdater;
			this->getMutex().unlock();
			return result;
		}

		// Public Setters
		void IBaseProcessInstance::setShouldRunUpdater(const bool runUpdater) {
			this->getMutex().lock();
			this->runUpdater = runUpdater;
			this->getMutex().unlock();
		}

		void IBaseProcessInstance::setLogger(::std::shared_ptr<::ando::logger::ILogger> logger) {
			this->getMutex().lock();
			this->logger->setLogger(logger);
			this->getMutex().unlock();
		}
		void IBaseProcessInstance::setProcessHandler(::std::shared_ptr<::ando::memory::IProcessHandler> processHandler) {
			this->getMutex().lock();
			this->processHandler = processHandler;
			this->getMutex().unlock();
		}

		// Protected Getters
		::std::mutex &IBaseProcessInstance::getMutex() {
			return this->_mutex;
		}

		::std::shared_ptr<::ando::logger::ISafeLogger> &IBaseProcessInstance::getLogger() {
			return this->logger;
		}
		::std::shared_ptr<::ando::memory::IProcessHandler> &IBaseProcessInstance::getProcessHandler() {
			return this->processHandler;
		}

		bool IBaseProcessInstance::hasProcessHandler() {
			this->getMutex().lock();
			bool result = (this->processHandler != nullptr);
			this->getMutex().unlock();
			return result;
		}

		bool IBaseProcessInstance::haveUpdatesStarted() {
			this->getMutex().lock();
			bool result = this->updatesStarted;
			this->getMutex().unlock();
			return result;
		}

		// Protected Setters
		void IBaseProcessInstance::setHaveUpdatesStarted(const bool updatesStarted) {
			this->getMutex().lock();
			this->updatesStarted = updatesStarted;
			this->getMutex().unlock();
		}
	}
}