#include "ISurfaceFontRenderer.hpp"


namespace ando {
	namespace overlay {
		namespace surface {
			::std::shared_ptr<ISurfaceFont> ISurfaceFontRenderer::getFont(const ::std::string name, const uint8_t size) {
				for (::std::size_t i = 0; i < this->fonts.size(); i++) {
					auto font = this->fonts.at(i);

					if ((font->getName().compare(name) != 0) || (font->getSize() != size))
						continue;

					return font;
				}

				return nullptr;
			}
			::std::shared_ptr<ISurfaceFont> ISurfaceFontRenderer::addFont(const ::std::string name, const uint8_t size, const uint16_t weight, const bool italics) {
				if (name.empty())
					return nullptr;

				std::shared_ptr<ISurfaceFont> newFont = ::std::make_shared<ISurfaceFont>(name, size, weight, italics, ::std::bind(&ando::overlay::surface::ISurfaceFontRenderer::FontInitializer, this, ::std::placeholders::_1));

				this->fonts.emplace_back(newFont);

				return newFont;
			}
			::std::shared_ptr<ISurfaceFont> ISurfaceFontRenderer::getOrCreateFont(const ::std::string name, const uint8_t size, const uint16_t weight, const bool italics) {
				auto font = this->getFont(name, size);
				if (font)
					return font;

				return this->addFont(name, size, weight, italics);
			}
			void ISurfaceFontRenderer::releaseFonts() {
				this->fonts.clear();
			}
		}
	}
}