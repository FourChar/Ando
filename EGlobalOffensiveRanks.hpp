#pragma once

#include <string>

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				enum ERanks {
					RANK_NONE,

					SILVER_I,
					SILVER_II,
					SILVER_III,
					SILVER_IV,
					SILVER_ELITE,
					SILVER_ELITE_MASTER,

					GOLD_NOVA_I,
					GOLD_NOVA_II,
					GOLD_NOVA_III,
					GOLD_NOVA_MASTER,

					MASTER_GUARDIAN_I,
					MASTER_GUARDIAN_II,
					MASTER_GUARDIAN_ELITE,
					DISTINGUISHED_MASTER_GUARDIAN,
					
					LEGENDARY_EAGLE,
					LEGENDARY_EAGLE_MASTER,
					SUPREME_MASTER_FIRST_CLASS,
					THE_GLOBAL_ELITE
				};

				extern const char *rankStrings[];
				::std::string rankIdToString(ERanks rank);
			}
		}
	}
}