#ifndef SHA1_HPP
#define SHA1_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <cstdint>
#include <iostream>
#include <string>

namespace ando {
	namespace cryptography {
		class SHA1 {
		private:
			uint32_t digest[5];
			::std::string buffer;
			uint64_t transforms;

		public:
			SHA1();

		public:
			void update(const ::std::string &str);
			void update(::std::istream &inputStream);

			::std::string final();

			static ::std::string hashFile(const ::std::string &fileName);
		};
	}
}

#endif // SHA1_HPP