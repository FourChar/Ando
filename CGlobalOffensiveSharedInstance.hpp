#pragma once

#include <string>

namespace ando {
	namespace process_specific {
		namespace CounterStrike {
			namespace GlobalOffensive {
				/*class ISharedInstance {
					virtual ~ISharedInstance() = 0;
				};

				template <typename T>
				class CSharedInstance : public ISharedInstance {
				private:
					::std::string name;
					T data;
					bool update;

				public:
					CSharedInstance(::std::string name, bool mustUpdate = true) {
						this->name = name;
						this->mustUpdate = mustUpdate;
					}

				public:
					::std::string getName() const {
						return this->name;
					}
					T &getData() {
						return this->data;
					}
					bool mustUpdate() const {
						return this->update;
					}

				public:
					void setName(const ::std::string name) {
						this->name = name;
					}
					void setMustUpdate(bool update) {
						this->update = update;
					}

					CSharedInstance &operator=(const T &data) {
						::std::memcpy(&this->data, &data, sizeof(T));
						return (*this);
					}
				};*/
			}
		}
	}
}