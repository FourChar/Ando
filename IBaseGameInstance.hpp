#ifndef IBASEGAMEINSTANCE_HPP
#define IBASEGAMEINSTANCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <vector>

#include "IBaseProcessInstance.hpp"
#include "IBaseGameShared.hpp"
#include "IBaseAndoEntity.hpp"
#include "CGameOffsetHandler.hpp"

#include "OverlayInstance.hpp"

#include "IProcessHandler.hpp"

namespace ando {
	namespace process_specific {
		template <typename SharedClass = ::ando::process_specific::IBaseGameShared, typename EntityClass = ::ando::process_specific::IBaseAndoEntity>
		class IBaseGameInstance : public IBaseProcessInstance {
		private: // Variables
			::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance;
			SharedClass *shared;
			::std::shared_ptr<::ando::process_specific::CGameOffsetHandler> offsetHandler;
			::std::vector<::std::shared_ptr<EntityClass>> entityList;

		public: // Constructors & Destructors
			IBaseGameInstance(::std::shared_ptr<::ando::logger::ILogger> logger, ::std::shared_ptr<::ando::memory::IProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
				: IBaseProcessInstance(logger, processHandler) {
				this->targetInstance = targetInstance;
				this->offsetHandler = ::std::make_shared<::ando::process_specific::CGameOffsetHandler>(logger);
			}
			IBaseGameInstance(::std::shared_ptr<::ando::memory::IProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
				: IBaseProcessInstance(processHandler) {
				this->targetInstance = targetInstance;
				this->offsetHandler = ::std::make_shared<::ando::process_specific::CGameOffsetHandler>();
			}
			IBaseGameInstance(::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance)
				: IBaseProcessInstance() {
				this->targetInstance = targetInstance;
				this->offsetHandler = ::std::make_shared<::ando::process_specific::CGameOffsetHandler>();
			}
			IBaseGameInstance()
				: IBaseProcessInstance() {
				this->targetInstance = nullptr;
				this->offsetHandler = ::std::make_shared<::ando::process_specific::CGameOffsetHandler>();
			}

			virtual ~IBaseGameInstance() {
				this->clearEntities();

				if (this->getShared() != nullptr)
					delete this->getShared();
			}

		public: // Public Functions
			void walkEntityList(::std::function<bool(::std::size_t index, SharedClass&, EntityClass&)> walkFunction) {
				if (this->isEntityListEmpty()) {
					return;
				}

				this->getMutex().lock();
				for (::std::size_t index = 0; index < this->getEntityList().size(); index++) {
					if (!walkFunction(index, *this->getShared(), *this->getEntityList().at(index)))
						break;
				}
				this->getMutex().unlock();
			}

			virtual bool worldToScreen(math::Vector3<float> from, math::Vector2<float> &to) = 0;

		protected: // Protected Functions
			virtual void initialize() = 0;

			const ::std::shared_ptr<::ando::overlay::OverlayInstance> getTargetInstance() const {
				return this->targetInstance;
			}

			::std::vector<::std::shared_ptr<EntityClass>> &getEntityList() {
				return this->entityList;
			}

			void addEntity(::std::shared_ptr<EntityClass> entity) {
				this->getMutex().lock();
				this->getEntityList().emplace_back(entity);
				this->getMutex().unlock();
			}
			void clearEntities() {
				this->getMutex().lock();
				this->getEntityList().clear();
				this->getMutex().unlock();
			}

			::std::shared_ptr<EntityClass> getEntityAtIndex(::std::size_t index) {
				this->getMutex().lock();
				if ((index < 0) || (index >= this->getEntityList().size())) {
					this->getMutex().unlock();
					return nullptr;
				}

				auto entity = this->getEntityList().at(index);
				this->getMutex().unlock();
				return entity;
			}
			void removeEntityAtIndex(::std::size_t index) {
				this->getMutex().lock();
				if ((index < 0) || (index >= this->getEntityList().size())) {
					this->getMutex().unlock();
					return nullptr;
				}

				this->getEntityList().erase(this->getEntityList().begin() + index, this->getEntityList().begin() + index + 1);
				this->getMutex().unlock();
			}

			bool isEntityListEmpty() {
				this->getMutex().lock();
				bool result = this->getEntityList().empty();
				this->getMutex().unlock();
				return result;
			}
			::std::size_t getEntityListSize() {
				this->getMutex().lock();
				::std::size_t size = this->getEntityList().size();
				this->getMutex().unlock();
				return size;
			}

			bool hasShared() {
				return (this->getShared() != nullptr);
			}

		public: // Public Setters
			void setTargetInstance(const ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance) {
				this->getMutex().lock();
				this->targetInstance = targetInstance;
				this->getMutex().unlock();
			}

		public: // Public Getters
			SharedClass *getShared() {
				return this->shared;
			}

		protected: // Protected Getters
			::std::shared_ptr<::ando::process_specific::CGameOffsetHandler> getOffsetHandler() {
				return this->offsetHandler;
			}

		protected: // Protected Setters
			void setShared(SharedClass *shared) {
				this->getMutex().lock();
				this->shared = shared;
				this->getMutex().unlock();
			}
		};
	}
}

#endif // IBASEGAMEINSTANCE_HPP