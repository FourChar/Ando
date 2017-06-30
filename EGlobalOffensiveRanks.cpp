#include "EGlobalOffensiveRanks.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {

				const char *rankStrings[] = {
					"-",
					"Silver I",
					"Silver II",
					"Silver III",
					"Silver IV",
					"Silver Elite",
					"Silver Elite Master",

					"Gold Nova I",
					"Gold Nova II",
					"Gold Nova III",
					"Gold Nova Master",
					"Master Guardian I",
					"Master Guardian II",

					"Master Guardian Elite",
					"Distinguished Master Guardian",
					"Legendary Eagle",
					"Legendary Eagle Master",
					"Supreme Master First Class",
					"The Global Elite"
				};

				::std::string rankIdToString(ERanks rank) {
					if ((rank < ERanks::RANK_NONE) || (rank > ERanks::THE_GLOBAL_ELITE))
						return "UNKNOWN";

					return rankStrings[static_cast<int>(rank)];
				}
			}
		}
	}
}