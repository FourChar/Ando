#ifndef CGLOBALOFFENSIVESHARED_HPP
#define CGLOBALOFFENSIVESHARED_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>
#include <array>

#include "IBaseGameShared.hpp"
#include "CGlobalOffensiveGlobalVars.hpp"
#include "CGlobalOffensiveBaseEntity.hpp"
#include "CGlobalOffensivePlayerResource.hpp"
//#include "CGlobalOffensiveSharedInstance.hpp"

#include "Matrix.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				class GameShared : public IBaseGameShared {
				private: // Variables
					//CSharedInstance<::ando::process_specific::CounterStrike::GlobalOffensive::CGlobalVars> _globalVars;
					//const ::std::array<ISharedInstance, 1> instances = { _globalVars };


					::ando::process_specific::CounterStrike::GlobalOffensive::CGlobalVars globalVars;
					::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity localPlayer;
					::ando::process_specific::CounterStrike::GlobalOffensive::CPlayerResource playerResource;
					::ando::math::Matrix<float, 4, 4> viewMatrix;

				public: // Constructors & Destructors
					GameShared();

				public: // Public Getters
					/*CSharedInstance<::ando::process_specific::CounterStrike::GlobalOffensive::CGlobalVars> &_getGlobalVars() {
						return this->_globalVars;
					}*/

					::ando::process_specific::CounterStrike::GlobalOffensive::CGlobalVars &getGlobalVars();
					::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity &getLocalPlayer();
					::ando::process_specific::CounterStrike::GlobalOffensive::CPlayerResource &getPlayerResource();
					::ando::math::Matrix<float, 4, 4> &getViewMatrix();
				};
			}
		}
	}
}

#endif // CGLOBALOFFENSIVESHARED_HPP