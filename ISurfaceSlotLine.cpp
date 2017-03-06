#include "ISurfaceSlotLine.hpp"
#include "ESurfaceCall.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				ISurfaceSlotLine::ISurfaceSlotLine() {
					this->setType(ESurfaceCall::DRAW_LINE);
				}

				// Getters
				float ISurfaceSlotLine::getX2() const {
					return this->x2;
				}
				float ISurfaceSlotLine::getY2() const {
					return this->y2;
				}

				// Setters
				void ISurfaceSlotLine::setX2(float x2) {
					this->x2 = x2;
				}
				void ISurfaceSlotLine::setY2(float y2) {
					this->y2 = y2;
				}
			}
		}
	}
}