#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			ISurfaceFont::ISurfaceFont(const std::string name, const uint8_t size, const uint16_t weight, const bool italics) {
				this->initialized = false;
				this->name = name;
				this->size = size;
				this->weight = weight;
				this->italics = italics;
				this->font = nullptr;
			}
			ISurfaceFont::ISurfaceFont(const std::string name, const uint8_t size, const uint16_t weight, const bool italics, fontInitializer initializer) {
				this->initialized = false;
				this->name = name;
				this->size = size;
				this->weight = weight;
				this->italics = italics;
				this->font = nullptr;

				this->initialized = initializer(this);
			}

			ISurfaceFont::~ISurfaceFont() { }

			void ISurfaceFont::initializeFont(fontInitializer initializer) {
				this->initialized = initializer(this);
			}

			bool ISurfaceFont::operator ==(const ISurfaceFont &rhs) {
				return ((this->name.compare(rhs.name) == 0) && (this->size == rhs.size) && (this->weight == rhs.weight) && (this->italics == rhs.italics));
			}
			bool ISurfaceFont::operator !=(const ISurfaceFont &rhs) {
				return !((*this) == rhs);
			}

			// Getters
			bool ISurfaceFont::isInitialized() const {
				return this->initialized;
			}
			std::string ISurfaceFont::getName() const {
				return this->name;
			}
			uint8_t ISurfaceFont::getSize() const {
				return this->size;
			}
			uint16_t ISurfaceFont::getWeight() const {
				return this->weight;
			}
			bool ISurfaceFont::isItalics() const {
				return this->italics;
			}
			ObjectType *ISurfaceFont::getFont() const {
				return const_cast<ObjectType *>(&this->font);
			}

			// Setters
			void ISurfaceFont::setInitialized(bool initialized) {
				this->initialized = initialized;
			}
			void ISurfaceFont::setName(std::string name) {
				this->name = name;
			}
			void ISurfaceFont::setSize(uint8_t size) {
				this->size = size;
			}
			void ISurfaceFont::setWeight(uint16_t weight) {
				this->weight = weight;
			}
			void ISurfaceFont::setItalics(bool italics) {
				this->italics = italics;
			}
		}
	}
}