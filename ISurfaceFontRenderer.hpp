#ifndef ISURFACE_FONT_RENDERER
#define ISURFACE_FONT_RENDERER

#ifdef _MSC_VER
#pragma once
#endif

#include <vector>

#include "ISurfaceBasicRenderer.hpp"
#include "ISurfaceFont.hpp"

namespace ando {
	namespace overlay {
		namespace surface {
			class ISurfaceFontRenderer : public ISurfaceBasicRenderer {
			private:
				std::vector<std::shared_ptr<ISurfaceFont>> fonts;

			public:
				std::shared_ptr<ISurfaceFont> getFont(const std::string name, const uint8_t size);
				std::shared_ptr<ISurfaceFont> addFont(const std::string name, const uint8_t size, const uint16_t weight, const bool italics);
				std::shared_ptr<ISurfaceFont> getOrCreateFont(const std::string name, const uint8_t size, const uint16_t weight = ISURFACE_TEXT_WEIGHT_DEFAULT, const bool italics = ISURFACE_TEXT_ITALICS_DEFAULT);

				void releaseFonts();

				virtual bool FontInitializer(const ISurfaceFont *font) = 0;
			};
		}
	}
}

#endif // ISURFACE_FONT_RENDERER