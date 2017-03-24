#ifndef CGLOBALOFFENSIVESCOREBOARDPLAYER_HPP
#define CGLOBALOFFENSIVESCOREBOARDPLAYER_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <string>

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			class CGlobalOffensiveInstance;

			class CGlobalOffensiveScoreboardPlayer {
				friend CGlobalOffensiveInstance;

			private: // Variables
				std::string m_szName;
				int m_iPing;
				int m_iKills;
				int m_iAssists;
				int m_iDeaths;
				bool m_bConnected;
				int m_iTeam;
				int m_iPendingTeam;
				bool m_bAlive;
				int m_iHealth;
				int m_iCompetitiveRanking;
				int m_iCompetitiveWins;

			public:
				CGlobalOffensiveScoreboardPlayer() {
					this->m_szName = "";
					this->m_iPing = 0;
					this->m_iKills = 0;
					this->m_iAssists = 0;
					this->m_iDeaths = 0;
					this->m_bConnected = false;
					this->m_iTeam = 0;
					this->m_iPendingTeam = 0;
					this->m_bAlive = false;
					this->m_iHealth = 0;
					this->m_iCompetitiveRanking = 0;
					this->m_iCompetitiveWins = 0;
				}

			public:
				CGlobalOffensiveScoreboardPlayer &operator =(const CGlobalOffensiveScoreboardPlayer &rhs) {
					this->m_szName = rhs.m_szName;
					this->m_iPing = rhs.m_iPing;
					this->m_iKills = rhs.m_iKills;
					this->m_iAssists = rhs.m_iAssists;
					this->m_iDeaths = rhs.m_iDeaths;
					this->m_bConnected = rhs.m_bConnected;
					this->m_iTeam = rhs.m_iTeam;
					this->m_iPendingTeam = rhs.m_iPendingTeam;
					this->m_bAlive = rhs.m_bAlive;
					this->m_iHealth = rhs.m_iHealth;
					this->m_iCompetitiveRanking = rhs.m_iCompetitiveRanking;
					this->m_iCompetitiveWins = rhs.m_iCompetitiveWins;
					return (*this);
				}

			public:
				std::string getName() { return this->m_szName; }
				int getPing() { return this->m_iPing; }
				int getKills() { return this->m_iKills; }
				int getAssists() { return this->m_iAssists; }
				int getDeaths() { return this->m_iDeaths; }
				bool isConnected() { return this->m_bConnected; }
				int getTeam() { return this->m_iTeam; }
				int getPendingTeam() { return this->m_iPendingTeam; }
				bool isAlive() { return this->m_bAlive; }
				int getHealth() { return this->m_iHealth; }
				int getCompetitiveRank() { return this->m_iCompetitiveRanking; }
				int getCompetitiveWins() { return this->m_iCompetitiveWins; }
			};
		}
	}
}

#endif // CGLOBALOFFENSIVESCOREBOARDPLAYER_HPP