#ifndef CGLOBALOFFENSIVEINSTANCE_HPP
#define CGLOBALOFFENSIVEINSTANCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#define ANDO_COUNTERSTRIKE_GLOBALOFFENSIVE_MAX_PLAYERS		64

#include <memory>
#include <vector>

#include "CProcessHandler.hpp"

#include "IBaseGameInstance.hpp"

#include "CGlobalOffensiveShared.hpp"
#include "CGlobalOffensiveBaseEntity.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			class CGlobalOffensiveInstance : public IBaseGameInstance<CGlobalOffensiveShared, CGlobalOffensiveBaseEntity> {
			private: // Variables
				::ando::memory::IModule *clientModule;
				::ando::memory::IModule *engineModule;

			public: // Constructors & Destructors
				CGlobalOffensiveInstance(::std::shared_ptr<::ando::logger::ILogger> logger, ::std::shared_ptr<::ando::memory::CProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance);
				CGlobalOffensiveInstance(::std::shared_ptr<::ando::memory::CProcessHandler> processHandler, ::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance);
				CGlobalOffensiveInstance(::std::shared_ptr<::ando::overlay::OverlayInstance> targetInstance);
				CGlobalOffensiveInstance();

				virtual ~CGlobalOffensiveInstance();

			public: // Public Functions
				virtual bool worldToScreen(::ando::math::Vector3<float> from, ::ando::math::Vector2<float> &to) override;

			protected: // Protected Functions
				virtual void initialize() override;

				virtual void processUpdate() override;

			private: // Private Functions
				::std::shared_ptr<::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity> readEntityFromIndex(::std::size_t index);
				bool readEntityFromAddress(::std::uintptr_t baseAddress, ::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity *entity);
			};
		}
	}
}

#endif // CGLOBALOFFENSIVEINSTANCE_HPP