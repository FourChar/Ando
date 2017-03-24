#include "ISurfaceSlotString.hpp"
#include "ESurfaceCall.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			namespace queue {
				ISurfaceSlotString::ISurfaceSlotString() {
					this->setType(ESurfaceCall::DRAW_RAW_STRING);
				}

				// Getters
				::std::shared_ptr<ando::overlay::surface::ISurfaceFont> ISurfaceSlotString::getFont() const {
					return this->font;
				}
				uint8_t ISurfaceSlotString::getSize() const {
					return this->size;
				}
				bool ISurfaceSlotString::isCentered() const {
					return this->centered;
				}
				::std::string ISurfaceSlotString::getText() const {
					return this->text;
				}

				// Setters
				void ISurfaceSlotString::setFont(::std::shared_ptr<ando::overlay::surface::ISurfaceFont> font) {
					this->font = font;
				}
				void ISurfaceSlotString::setSize(uint8_t size) {
					this->size = size;
				}
				void ISurfaceSlotString::setCentered(bool centered) {
					this->centered = centered;
				}
				void ISurfaceSlotString::setText(::std::string text) {
					this->text = text;
				}
			}
		}
	}
}