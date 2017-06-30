#pragma once

#include <string>
#include <vector>

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				namespace Bones {
					class CBone {
					private:
						::std::size_t id;
						::std::string name;

					public:
						CBone(::std::size_t id, ::std::string name);

					public:
						::std::size_t getId() const;
						::std::string getName() const;

					public:
						void setId(const ::std::size_t id);
						void setName(const ::std::string name);
					};

					::std::size_t getBoneIdByName(::std::vector<CBone> bones, ::std::string name);

					extern const ::std::vector<CBone> terroristBones;
				}
			}
		}
	}
}