#pragma once

#include <functional>
#include <vector>

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				namespace Bones {
					class CConsecutiveBoneStructure {
					private:
						::std::vector<::std::size_t> bones;

					public:
						CConsecutiveBoneStructure(::std::vector<::std::size_t> bones) {
							this->bones = bones;
						}

					public:
						bool iterateBones(::std::function<bool(const ::std::size_t previous, const ::std::size_t current, const ::std::size_t next)> func) const {
							::std::size_t previous = -1;
							::std::size_t current = -1;
							::std::size_t next = -1;

							for (auto it = this->bones.begin(); it != this->bones.end(); it++) {
								previous = current;
								current = (*it);

								if ((it + 1) != this->bones.end())
									next = (*(it + 1));
								else
									next = -1;

								if (!func(previous, current, next))
									return false;
							}

							return true;
						}
					};
				}
			}
		}
	}
}