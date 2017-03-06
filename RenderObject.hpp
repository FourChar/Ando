#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include "ObjectManager.hpp"
#include "Color.hpp"

namespace ando {
	class RenderObject {
	private:
		ObjectType object;
		Color color;
	};
}

#endif // RENDER_OBJECT_HPP