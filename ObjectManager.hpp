#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <vector>
#include <memory>
#include <utility>

typedef void* ObjectType;

namespace ando {
	class ObjectManager {
	public:
		bool add(std::string name, ObjectType object);
		bool remove(std::string name);

		ObjectType get(std::string name);

		bool update(std::string name, ObjectType object);

	private:
		std::vector<std::pair<std::string, ObjectType>> objects;
	};
}

#endif // OBJECT_MANAGER_HPP