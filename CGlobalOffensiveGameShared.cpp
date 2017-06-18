#include "CGlobalOffensiveGameShared.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				GameShared::GameShared() { }

				::ando::process_specific::CounterStrike::GlobalOffensive::CGlobalVars &GameShared::getGlobalVars() {
					return this->globalVars;
				}
				::ando::process_specific::CounterStrike::GlobalOffensive::CBaseEntity &GameShared::getLocalPlayer() {
					return this->localPlayer;
				}
				::ando::process_specific::CounterStrike::GlobalOffensive::CPlayerResource &GameShared::getPlayerResource() {
					return this->playerResource;
				}
				::ando::math::Matrix<float, 4, 4> &GameShared::getViewMatrix() {
					return this->viewMatrix;
				}
			}
		}
	}
}