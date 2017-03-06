#include "ISurfaceSlotRectangle.hpp"
#include "ESurfaceCall.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				ISurfaceSlotRectangle::ISurfaceSlotRectangle(bool filled) {
					if (filled)
						this->setType(ESurfaceCall::FILL_RECTANGLE);
					else
						this->setType(ESurfaceCall::DRAW_RECTANGLE);
				}

				// Getters
				float ISurfaceSlotRectangle::getWidth() const {
					return this->height;
				}
				float ISurfaceSlotRectangle::getHeight() const {
					return this->width;
				}

				// Setters
				void ISurfaceSlotRectangle::setWidth(float width) {
					this->width = width;
				}
				void ISurfaceSlotRectangle::setHeight(float height) {
					this->height = height;
				}
			}
		}
	}
}