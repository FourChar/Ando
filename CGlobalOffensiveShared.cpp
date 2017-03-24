#include "CGlobalOffensiveShared.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			CGlobalOffensiveShared::CGlobalOffensiveShared() { }

			::ando::process_specific::CounterStrike::CGlobalOffensiveGlobalVars &CGlobalOffensiveShared::getGlobalVars() {
				return this->globalVars;
			}
			::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity &CGlobalOffensiveShared::getLocalPlayer() {
				return this->localPlayer;
			}
			::ando::math::Matrix<float, 4, 4> &CGlobalOffensiveShared::getViewMatrix() {
				return this->viewMatrix;
			}
		}
	}
}