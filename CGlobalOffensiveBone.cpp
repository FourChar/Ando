#include "CGlobalOffensiveBone.hpp"

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				namespace Bones {
					CBone::CBone(::std::size_t id, ::std::string name) {
						this->id = id;
						this->name = name;
					}

					::std::size_t CBone::getId() const {
						return this->id;
					}
					::std::string CBone::getName() const {
						return this->name;
					}

					void CBone::setId(const ::std::size_t id) {
						this->id = id;
					}
					void CBone::setName(const ::std::string name) {
						this->name = name;
					}

					::std::size_t getBoneIdByName(::std::vector<CBone> bones, ::std::string name) {
						for (auto it = bones.begin(); it != bones.end(); it++) {
							if (it->getName().compare(name) == 0)
								return it->getId();
						}

						return -1;
					}

					const ::std::vector<CBone> terroristBones = {
						CBone(0, "center_of_mass"),
						CBone(1, "origin"),

						CBone(3, "spine_0"),
						CBone(4, "spine_1"),
						CBone(5, "spine_2"),
						CBone(6, "spine_3"),
						CBone(7, "neck"),
						CBone(8, "head"),

						CBone(10, "shoulder_left"),
						CBone(11, "elbow_left"),
						CBone(12, "hand_left"),

						CBone(38, "shoulder_right"),
						CBone(39, "elbow_right"),
						CBone(40, "hand_right"),

						CBone(65, "pelvis_left"),
						CBone(66, "knee_left"),
						CBone(67, "ankle_left"),

						CBone(72, "pelvis_right"),
						CBone(73, "knee_right"),
						CBone(74, "ankle_right")
					};
				}
			}
		}
	}
}