#pragma once

#include <functional>
#include <vector>

#include "CGlobalOffensiveConsecutiveBoneStructure.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				namespace Bones {
					class CSkeletonChain {
					private:
						::std::vector<CConsecutiveBoneStructure> boneStructures;

					public:
						CSkeletonChain(::std::vector<CConsecutiveBoneStructure> boneStructures) {
							this->boneStructures = boneStructures;
						}

					public:
						void iterateStructures(::std::function<bool(const CConsecutiveBoneStructure *currentStructure)> func) const {
							CConsecutiveBoneStructure *current = nullptr;

							for (auto it = this->boneStructures.begin(); it != this->boneStructures.end(); it++) {
								current = const_cast<CConsecutiveBoneStructure *>(&(*it));

								if (!func(current))
									break;
							}
						}
					};

					extern const CSkeletonChain terroristSkeleton;
					extern const CSkeletonChain counterTerroristSkeleton;
				}
			}
		}
	}
}