#ifndef COLOR_HPP
#define COLOR_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cstdint>

namespace ando {
	class Color {
	private:
		uint8_t uColor[4];

	public:
		Color();
		Color(const Color &col);
		Color(uint8_t uColor[4]);
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		Color(unsigned long hex);
		
	public:
		int operator [](int index);
		Color operator =(const Color &rhs);
		bool operator ==(const Color &rhs);
		bool operator !=(const Color &rhs);

	public:
		uint8_t r() const;
		uint8_t g() const;
		uint8_t b() const;
		uint8_t a() const;
		
		unsigned long rgba() const;
		unsigned long rgb() const;
		
	public:
		Color &setR(uint8_t r);
		Color &setG(uint8_t g);
		Color &setB(uint8_t b);
		Color &setA(uint8_t a);
		
		void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void set(unsigned long hex);
	};

	namespace colors {
		extern Color black;
		extern Color white;
		extern Color red;
		extern Color green;
		extern Color blue;
	}
}

#endif // COLOR_HPP