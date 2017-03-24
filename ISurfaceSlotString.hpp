#ifndef ISURFACE_SLOT_STRING
#define ISURFACE_SLOT_STRING

#ifdef _MSC_VER
#pragma once
#endif

#include <memory>

#include "ISurfaceSlot.hpp"
#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				class ISurfaceSlotString : public ISurfaceSlot {
				private:
					std::shared_ptr<ando::overlay::surface::ISurfaceFont> font;
					uint8_t size;
					bool centered;
					std::string text;

				public:
					ISurfaceSlotString();

				public: // Getters
					std::shared_ptr<ando::overlay::surface::ISurfaceFont> getFont() const;
					uint8_t getSize() const;
					bool isCentered() const;
					std::string getText() const;

				public: // Setters
					void setFont(::std::shared_ptr<ando::overlay::surface::ISurfaceFont> font);
					void setSize(uint8_t size);
					void setCentered(bool centered);
					void setText(::std::string text);
				};
			}
		}
	}
}

#endif // ISURFACE_SLOT_STRING