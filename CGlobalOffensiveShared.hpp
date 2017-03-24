#ifndef CGLOBALOFFENSIVESHARED_HPP
#define CGLOBALOFFENSIVESHARED_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>

#include "IBaseGameShared.hpp"
#include "CGlobalOffensiveGlobalVars.hpp"
#include "CGlobalOffensiveBaseEntity.hpp"
#include "CGlobalOffensivePlayerResource.hpp"

#include "Matrix.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			class CGlobalOffensiveShared : public IBaseGameShared {
			private: // Variables
				::ando::process_specific::CounterStrike::CGlobalOffensiveGlobalVars globalVars;
				::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity localPlayer;
				::ando::math::Matrix<float, 4, 4> viewMatrix;

			public: // Constructors & Destructors
				CGlobalOffensiveShared();

			public: // Public Getters
				::ando::process_specific::CounterStrike::CGlobalOffensiveGlobalVars &getGlobalVars();
				::ando::process_specific::CounterStrike::CGlobalOffensiveBaseEntity &getLocalPlayer();
				::ando::math::Matrix<float, 4, 4> &getViewMatrix();
			};
		}
	}
}

#endif // CGLOBALOFFENSIVESHARED_HPP