#ifndef ISURFACE_SLOT_LINE
#define ISURFACE_SLOT_LINE

#ifdef _MSC_VER
#pragma once
#endif

#include "ISurfaceSlot.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				class ISurfaceSlotLine : public ISurfaceSlot {
				private:
					float x2;
					float y2;

				public:
					ISurfaceSlotLine();

				public: // Getters
					float getX2() const;
					float getY2() const;

				public: // Setters
					void setX2(float x2);
					void setY2(float y2);
				};
			}
		}
	}
}

#endif // ISURFACE_SLOT_LINE