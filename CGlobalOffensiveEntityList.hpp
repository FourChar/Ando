#pragma once

#include <vector>

#include "CGlobalOffensiveEntityInfo.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				class CGlobalOffensiveEntityList {
				private:
					::std::vector<CEntityInfo> entities;

				public:
					CGlobalOffensiveEntityList() {

					}

				public:
					CGlobalOffensiveEntityList &operator =(const CGlobalOffensiveEntityList &rhs) {
						::std::vector<CEntityInfo> newEntities(rhs.entities);

						this->entities = newEntities;

						return (*this);
					}

				public:
					::std::vector<CEntityInfo> &getEntities() {
						return this->entities;
					}
				};
			}
		}
	}
}