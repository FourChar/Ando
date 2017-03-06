#include "ISurfaceSlot.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				// Getters
				ESurfaceCall ISurfaceSlot::getType() const {
					return this->type;
				}
				float ISurfaceSlot::getX() const {
					return this->x;
				}
				float ISurfaceSlot::getY() const {
					return this->y;
				}
				ando::Color ISurfaceSlot::getColor() const {
					return this->color;
				}

				// Setters
				void ISurfaceSlot::setType(ESurfaceCall type) {
					this->type = type;
				}
				void ISurfaceSlot::setX(float x) {
					this->x = x;
				}
				void ISurfaceSlot::setY(float y) {
					this->y = y;
				}
				void ISurfaceSlot::setColor(ando::Color color) {
					this->color = color;
				}
			}
		}
	}
}