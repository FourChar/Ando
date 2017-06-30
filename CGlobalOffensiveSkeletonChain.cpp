#include "CGlobalOffensiveSkeletonChain.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				namespace Bones {
					const CSkeletonChain terroristSkeleton({
						CConsecutiveBoneStructure({
							3, // spine_0
							4, // spine_1
							5, // spine_2
							6, // spine_3
							7, // neck
							8  //head
						}),
						CConsecutiveBoneStructure({
							7,  // neck
							10, // shoulder_left
							11, // elbow_left
							12  // wrist_left
						}),
						CConsecutiveBoneStructure({
							7,  // neck
							38, // shoulder_right
							39, // elbow_right
							40, // wrist_right
						}),
						CConsecutiveBoneStructure({
							3,  // spine_0
							65, // pelvis_left
							66, // knee_left
							67  // ankle_left
						}),
						CConsecutiveBoneStructure({
							3,  // spine_0
							72, // pelvis_right
							73, // knee_right
							74  // ankle_right
						})
					});

					const CSkeletonChain counterTerroristSkeleton({
						CConsecutiveBoneStructure({
							3, // spine_0
							4, // spine_1
							5, // spine_2
							6, // spine_3
							7, // neck
							8  //head
						}),
						CConsecutiveBoneStructure({
							7,  // neck
							11, // shoulder_left
							12, // elbow_left
							13  // wrist_left
						}),
						CConsecutiveBoneStructure({
							7,  // neck
							40, // shoulder_right
							41, // elbow_right
							42, // wrist_right
						}),
						CConsecutiveBoneStructure({
							3,  // spine_0
							72, // pelvis_left
							73, // knee_left
							74  // ankle_left
						}),
						CConsecutiveBoneStructure({
							3,  // spine_0
							81, // pelvis_right
							82, // knee_right
							83  // ankle_right
						})
					});
				}
			}
		}
	}
}