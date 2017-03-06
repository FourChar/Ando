#include "Color.hpp"

namespace ando {
	Color::Color() {
		this->uColor[0] = this->uColor[1] = this->uColor[2] = this->uColor[3] = 0;
	}
	Color::Color(const Color &col) {
		this->uColor[0] = col.uColor[0];
		this->uColor[1] = col.uColor[1];
		this->uColor[2] = col.uColor[2];
		this->uColor[3] = col.uColor[3];
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
	
	void Color::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		this->setR(r);
		this->setG(g);
		this->setB(b);
		this->setA(a);
	}
	void Color::set(unsigned long hex) {
		this->uColor[0] = (uint8_t)((hex >> 16) & 0xFF);
		this->uColor[1] = (uint8_t)((hex >> 8) & 0xFF);
		this->uColor[3] = (uint8_t)((hex >> 24) & 0xFF);
		this->uColor[2] = (uint8_t)(hex & 0xFF);
	}

	namespace colors {
		Color black(0, 0, 0, 255);
		Color white(255, 255, 255, 255);
		Color red(255, 0, 0, 255);
		Color green(0, 255, 0, 255);
		Color blue(0, 0, 255, 255);
	}
}