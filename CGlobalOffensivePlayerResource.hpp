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
			namespace GlobalOffensive {
				class CInstance;

				class CPlayerResource {
					friend CInstance;

				private: // Variables
					::std::vector<::ando::process_specific::CounterStrike::GlobalOffensive::CScoreboardPlayer *> scoreboardPlayers;

				public: // Constructors & Destructors
					CPlayerResource(::std::size_t reserveSize = 65) {
						this->scoreboardPlayers.reserve(reserveSize);

						for (::std::size_t i = 0; i < reserveSize; i++) {
							this->scoreboardPlayers.emplace_back(new ::ando::process_specific::CounterStrike::GlobalOffensive::CScoreboardPlayer());
						}
					}

					~CPlayerResource() {
						for (::std::size_t i = 0; i < this->scoreboardPlayers.size(); i++) {
							if(this->scoreboardPlayers.at(i))
								delete this->scoreboardPlayers.at(i);
						}

						this->scoreboardPlayers.clear();
					}

				public: // Public Functions
					::ando::process_specific::CounterStrike::GlobalOffensive::CScoreboardPlayer *getScoreboardPlayer(::std::size_t index) {
						if ((index < 0) || (index >= this->scoreboardPlayers.size()))
							return nullptr;

						return this->scoreboardPlayers.at(index);
					}

					::ando::process_specific::CounterStrike::GlobalOffensive::CPlayerResource &operator =(const ::ando::process_specific::CounterStrike::GlobalOffensive::CPlayerResource &rhs) {
						if (this->scoreboardPlayers.size() > rhs.scoreboardPlayers.size()) {
							this->scoreboardPlayers.erase(this->scoreboardPlayers.begin() + rhs.scoreboardPlayers.size(), this->scoreboardPlayers.end());
						}
						else if (this->scoreboardPlayers.size() < rhs.scoreboardPlayers.size()) {
							this->scoreboardPlayers.reserve(rhs.scoreboardPlayers.size());
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
}

#endif // CGLOBALOFFENSIVEPLAYERRESOURCE_HPP