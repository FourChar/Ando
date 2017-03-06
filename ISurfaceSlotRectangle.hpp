#ifndef ISURFACE_SLOT_RECTANGLE
#define ISURFACE_SLOT_RECTANGLE

#ifdef _MSC_VER
#pragma once
#endif

#include "ISurfaceSlot.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				class ISurfaceSlotRectangle : public ISurfaceSlot {
				private:
					float width;
					float height;

				public:
					ISurfaceSlotRectangle(bool filled = false);

				public: // Getters
					float getWidth() const;
					float getHeight() const;

				public: // Setters
					void setWidth(float width);
					void setHeight(float height);
				};
			}
		}
	}
}

#endif // ISURFACE_SLOT_RECTANGLE