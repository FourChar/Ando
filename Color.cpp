#include "Color.hpp"

namespace ando {
	Color::Color() {
		this->uColor[0] = this->uColor[1] = this->uColor[2] = this->uColor[3] = 0;
	}
	Color::Color(const Color &col) {
		for (int i = 0; i < 4; i++)
			this->uColor[i] = col.uColor[i];
	}
	Color::Color(uint8_t uColor[4]) {
		for(int i = 0; i < 4; i++)
			this->uColor[i] = uColor[i];
	}
	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		this->setR(r);
		this->setG(g);
		this->setB(b);
		this->setA(a);
	}
	Color::Color(unsigned long hex) {
		this->set(hex);
	}
	
	int Color::operator [](int index) {
		if((index < 0) || (index > 3)) {
			return -1;
		}
		
		return this->uColor[index];
	}
	Color Color::operator =(const Color &rhs) {
		for (int i = 0; i < 4; i++) {
			this->uColor[i] = rhs.uColor[i];
		}
		return (*this);
	}
	bool Color::operator ==(const Color &rhs) {
		return (
			(this->r() == rhs.r()) &&
			(this->g() == rhs.g()) &&
			(this->b() == rhs.b()) &&
			(this->a() == rhs.a())
			);
	}
	bool Color::operator !=(const Color &rhs) {
		return (
			(this->r() != rhs.r()) ||
			(this->g() != rhs.g()) ||
			(this->b() != rhs.b()) ||
			(this->a() != rhs.a())
			);
	}

	uint8_t Color::r() const {
		return this->uColor[0];
	}
	uint8_t Color::g() const {
		return this->uColor[1];
	}
	uint8_t Color::b() const {
		return this->uColor[2];
	}
	uint8_t Color::a() const {
		return this->uColor[3];
	}
		
	unsigned long Color::rgba() const {
		unsigned long hexColor = ((unsigned long)this->uColor[3] << 24);
		hexColor |= ((unsigned long)this->uColor[0] << 16);
		hexColor |= ((unsigned long)this->uColor[1] << 8);
		hexColor |= ((unsigned long)this->uColor[2]);
		return hexColor;
	}
	unsigned long Color::rgb() const {
		unsigned long hexColor = ((unsigned long)this->uColor[0] << 16);
		hexColor |= ((unsigned long)this->uColor[1] << 8);
		hexColor |= ((unsigned long)this->uColor[2]);
		return hexColor;
	}
	
	Color &Color::setR(uint8_t r) {
		this->uColor[0] = r;
		return (*this);
	}
	Color &Color::setG(uint8_t g) {
		this->uColor[1] = g;
		return (*this);
	}
	Color &Color::setB(uint8_t b) {
		this->uColor[2] = b;
		return (*this);
	}
	Color &Color::setA(uint8_t a) {
		this->uColor[3] = a;
		return (*this);
	}
	
	Color &Color::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		this->setR(r);
		this->setG(g);
		this->setB(b);
		this->setA(a);
		return (*this);
	}
	Color &Color::set(unsigned long hex) {
		this->uColor[0] = (uint8_t)((hex >> 16) & 0xFF);
		this->uColor[1] = (uint8_t)((hex >> 8) & 0xFF);
		this->uColor[3] = (uint8_t)((hex >> 24) & 0xFF);
		this->uColor[2] = (uint8_t)(hex & 0xFF);
		return (*this);
	}

	namespace colors {
		Color invisible(0, 0, 0, 0);
		Color black(0, 0, 0);
		Color white(255, 255, 255);

		Color red(255, 0, 0);
		Color green(0, 255, 0);
		Color blue(0, 0, 255);

		namespace reds {
			Color vanillaIce(242, 215, 213);
			Color shilo(230, 176, 170);
			Color newYorkPink(217, 136, 128);
			Color chestnutRose(205, 97, 85);
			Color tallPoppy(192, 57, 43);
			Color mexicanRed(169, 50, 38);
			Color oldBrick(146, 43, 33);
			Color mocha(123, 36, 28);
			Color cherrywood(100, 30, 22);
			Color azalea(250, 219, 216);
			Color mandysPink(245, 183, 177);
			Color apricot(241, 148, 138);
			Color burntSienna(236, 112, 99);
			Color cinnabar(231, 76, 60);
			Color flushMahogany(203, 67, 53);
			Color burntUmber(148, 49, 38);
			Color metalicCopper(120, 40, 31);
		}

		namespace purples {
			Color prelude(215, 189, 226);
			Color lightWisteria(195, 155, 211);
			Color eastSide(175, 122, 197);
			Color wisteria(155, 89, 182);
			Color affair(136, 78, 160);
			Color bossanova(81, 46, 95);
		}

		namespace blues {
			Color regentStBlue(169, 204, 227);
			Color halfBaked(127, 179, 213);
			Color danube(84, 153, 199);
			Color mariner(41, 128, 185);
			Color jellyBean(36, 113, 163);
			Color matisse(31, 97, 141);
			Color blumine(26, 82, 118);
			Color biscay(21, 67, 96);
			Color blizzardBlue(174, 214, 241);
			Color seagull(133, 193, 233);
			Color pictonBlue(93, 173, 226);
			Color curiousBlue(52, 152, 219);
		}
	}
}