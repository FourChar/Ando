#ifndef ISURFACE_SLOT
#define ISURFACE_SLOT

#ifdef _MSC_VER
#pragma once
#endif

#include "ESurfaceCall.hpp"
#include "Color.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				class ISurfaceSlot {
				private:
					ESurfaceCall type;

					float x;
					float y;
					ando::Color color;

				public: // Getters
					ESurfaceCall getType() const;
					float getX() const;
					float getY() const;
					ando::Color getColor() const;

				public: // Setters
					void setType(ESurfaceCall type);
					void setX(float x);
					void setY(float y);
					void setColor(ando::Color color);
				};
			}
		}
	}
}

#endif // ISURFACE_SLOT_HPP