#ifndef ISURFACE_FONT
#define ISURFACE_FONT

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <functional>

#define ISURFACE_OUTLINE_ALPHA			170
#define ISURFACE_TEXT_SIZE_DEFAULT		16
#define ISURFACE_TEXT_WEIGHT_DEFAULT	400
#define ISURFACE_TEXT_ITALICS_DEFAULT	false
#define ISURFACE_TEXT_CENTERED_DEFAULT	false

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceFont;

			typedef ::std::function<bool(const ando::overlay::surface::ISurfaceFont *font)> fontInitializer;

			class ISurfaceFont {
			private:
				bool initialized;
				std::string name;
				uint8_t size;
				uint16_t weight;
				bool italics;
				void *font;

			public:
				ISurfaceFont(const ::std::string name, const uint8_t size = ISURFACE_TEXT_SIZE_DEFAULT, const uint16_t weight = ISURFACE_TEXT_WEIGHT_DEFAULT, const bool italics = ISURFACE_TEXT_ITALICS_DEFAULT);
				ISurfaceFont(const ::std::string name, const uint8_t size, const uint16_t weight, const bool italics, fontInitializer initializer);

				~ISurfaceFont();

				void initializeFont(fontInitializer initializer);

			public:
				bool operator ==(const ISurfaceFont &rhs);
				bool operator !=(const ISurfaceFont &rhs);

			public: // Getters
				bool isInitialized() const;
				std::string getName() const;
				uint8_t getSize() const;
				uint16_t getWeight() const;
				bool isItalics() const;
				void **getFont() const;

			public: // Setters
				void setInitialized(bool initialized);
				void setName(::std::string name);
				void setSize(uint8_t size);
				void setWeight(uint16_t weight);
				void setItalics(bool italics);
			};
		}
	}
}

#endif // ISURFACE_FONT