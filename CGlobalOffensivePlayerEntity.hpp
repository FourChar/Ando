#pragma once

#include <memory>

#include "CGlobalOffensiveBaseEntity.hpp"
#include "CGlobalOffensiveScoreboardPlayer.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				class CInstance;

				class CPlayerEntity : public CBaseEntity {
					friend CInstance;

				private:
					ando::process_specific::CounterStrike::GlobalOffensive::CScoreboardPlayer *scoreboardPlayer;

				public:
					CPlayerEntity &operator=(const CPlayerEntity &rhs) {
						CBaseEntity::operator=(rhs);

						this->scoreboardPlayer = rhs.scoreboardPlayer;
					}

				public:
					CScoreboardPlayer *getScoreboardPlayer() const {
						return this->scoreboardPlayer;
					}
				};
			}
		}
	}
}