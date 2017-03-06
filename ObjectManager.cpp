#include "ObjectManager.hpp"

namespace ando {
	bool ObjectManager::add(std::string name, ObjectType object) {
		ObjectType storedObject = this->get(name);
		if (storedObject != nullptr)
			return false;

		this->objects.push_back(std::make_pair(name, (ObjectType)(object)));
		return true;
	}
	bool ObjectManager::remove(std::string name) {
		for (std::size_t i = 0; i < this->objects.size(); i++) {
			auto current = this->objects.at(i);

			if (current.first.compare(name) == 0) {
				this->objects.erase(this->objects.begin() + i);
				return true;
			}
		}

		return false;
	}

	bool ObjectManager::update(std::string name, ObjectType object) {
		for (auto it = this->objects.begin(); it != this->objects.end(); it++) {
			if (it->first.compare(name) == 0) {
				it->second = (ObjectType)(object);
				return true;
			}
		}

		return false;
	}

	ObjectType ObjectManager::get(std::string name) {
		for (std::vector<std::pair<std::string, ObjectType>>::iterator it = this->objects.begin(); it != this->objects.end(); it++) {
			if (it->first.compare(name) == 0)
				return it->second;
		}

		return nullptr;
	}
}
