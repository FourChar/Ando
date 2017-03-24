#ifndef CGLOBALOFFENSIVEPLAYERRESOURCE_HPP
#define CGLOBALOFFENSIVEPLAYERRESOURCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <vector>

#include "CGlobalOffensiveScoreboardPlayer.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			class CGlobalOffensiveInstance;

			class CGlobalOffensivePlayerResource {
				friend CGlobalOffensiveInstance;

			private: // Variables
				::std::vector<::ando::process_specific::CounterStrike::CGlobalOffensiveScoreboardPlayer *> scoreboardPlayers;

			public: // Constructors & Destructors
				CGlobalOffensivePlayerResource(::std::size_t reserveSize = 65) {
					this->scoreboardPlayers.reserve(reserveSize);

					for (::std::size_t i = 0; i < reserveSize; i++) {
						this->scoreboardPlayers.emplace_back(new ::ando::process_specific::CounterStrike::CGlobalOffensiveScoreboardPlayer());
					}
				}

				~CGlobalOffensivePlayerResource() {
					for (::std::size_t i = 0; i < this->scoreboardPlayers.size(); i++) {
						delete this->scoreboardPlayers.at(i);
					}
				}

			public: // Public Functions
				::ando::process_specific::CounterStrike::CGlobalOffensiveScoreboardPlayer *getScoreboardPlayer(::std::size_t index) {
					if ((index < 0) || (index >= this->scoreboardPlayers.size()))
						return nullptr;

					return this->scoreboardPlayers.at(index);
				}

				::ando::process_specific::CounterStrike::CGlobalOffensivePlayerResource &operator =(const ::ando::process_specific::CounterStrike::CGlobalOffensivePlayerResource &rhs) {
					if (this->scoreboardPlayers.size() > rhs.scoreboardPlayers.size()) {
						this->scoreboardPlayers.erase(this->scoreboardPlayers.begin() + rhs.scoreboardPlayers.size(), this->scoreboardPlayers.end());
					}

					for (::std::size_t i = 0; i < this->scoreboardPlayers.size(); i++) {
						(*this->scoreboardPlayers.at(i)) = (*rhs.scoreboardPlayers.at(i));
					}

					return (*this);
				}
			};
		}
	}
}

#endif // CGLOBALOFFENSIVEPLAYERRESOURCE_HPP