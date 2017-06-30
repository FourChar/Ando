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
		
		Color &set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		Color &set(unsigned long hex);
	};

	namespace colors {
		extern Color invisible;
		extern Color black;
		extern Color white;

		extern Color red;
		extern Color green;
		extern Color blue;

		namespace reds {
			extern Color fantasy;
			extern Color vanillaIce;
			extern Color shilo;
			extern Color newYorkPink;
			extern Color chestnutRose;
			extern Color tallPoppy;
			extern Color mexicanRed;
			extern Color oldBrick;
			extern Color mocha;
			extern Color cherrywood;
			extern Color provincialPink;
			extern Color azalea;
			extern Color mandysPink;
			extern Color apricot;
			extern Color burntSienna;
			extern Color cinnabar;
			extern Color flushMahogany;
		}

		namespace purples {
			extern Color prelude;
			extern Color lightWisteria;
			extern Color eastSide;
			extern Color wisteria;
			extern Color affair;
			extern Color bossanova;
		}

		namespace blues {
			extern Color regentStBlue;
			extern Color halfBaked;
			extern Color danube;
			extern Color mariner;
			extern Color jellyBean;
			extern Color matisse;
			extern Color blumine;
			extern Color biscay;
			extern Color blizzardBlue;
			extern Color seagull;
			extern Color pictonBlue;
			extern Color curiousBlue;
		}
	}
}

#endif // COLOR_HPP