#include "SHA1.hpp"

#include <sstream>
#include <fstream>
#include <iomanip>

namespace ando {
	namespace cryptography {
		static const ::std::size_t BLOCK_INTS = 16;
		static const ::std::size_t BLOCK_BYTES = BLOCK_INTS * 4;

		static void reset(::std::uint32_t digest[], ::std::string &buffer, ::std::uint64_t &transforms) {
			digest[0] = 0x67452301;
			digest[1] = 0xEFCdAB89;
			digest[2] = 0x98BADCFE;
			digest[3] = 0x10325476;
			digest[4] = 0xC3D2E1F0;

			buffer = "";
			transforms = 0;
		}

		static ::std::uint32_t rol(const ::std::uint32_t value, const ::std::size_t bits) {
			return (value << bits) | (value >> (32 - bits));
		}

		static ::std::uint32_t blk(const ::std::uint32_t block[BLOCK_INTS], const ::std::size_t i) {
			return rol(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i], 1);
		}

		static void R0(const ::std::uint32_t block[BLOCK_INTS], const ::std::uint32_t v, ::std::uint32_t &w, const ::std::uint32_t x, const ::std::uint32_t y, ::std::uint32_t &z, const ::std::size_t i) {
			z += ((w & (x ^ y)) ^ y) + block[i] + 0x5A827999 + rol(v, 5);
			w = rol(w, 30);
		}


		static void R1(::std::uint32_t block[BLOCK_INTS], const::std::uint32_t v, ::std::uint32_t &w, const ::std::uint32_t x, const ::std::uint32_t y, ::std::uint32_t &z, const ::std::size_t i) {
			block[i] = blk(block, i);
			z += ((w & (x ^ y)) ^ y) + block[i] + 0x5A827999 + rol(v, 5);
			w = rol(w, 30);
		}


		static void R2(::std::uint32_t block[BLOCK_INTS], const ::std::uint32_t v, ::std::uint32_t &w, const ::std::uint32_t x, const ::std::uint32_t y, ::std::uint32_t &z, const ::std::size_t i) {
			block[i] = blk(block, i);
			z += (w ^ x ^ y) + block[i] + 0x6ED9EBA1 + rol(v, 5);
			w = rol(w, 30);
		}


		static void R3(::std::uint32_t block[BLOCK_INTS], const ::std::uint32_t v, ::std::uint32_t &w, const ::std::uint32_t x, const ::std::uint32_t y, ::std::uint32_t &z, const ::std::size_t i) {
			block[i] = blk(block, i);
			z += (((w | x) & y) | (w & x)) + block[i] + 0x8F1BBCDC + rol(v, 5);
			w = rol(w, 30);
		}


		static void R4(::std::uint32_t block[BLOCK_INTS], const ::std::uint32_t v, ::std::uint32_t &w, const ::std::uint32_t x, const ::std::uint32_t y, ::std::uint32_t &z, const ::std::size_t i) {
			block[i] = blk(block, i);
			z += (w ^ x ^ y) + block[i] + 0xCA62C1D6 + rol(v, 5);
			w = rol(w, 30);
		}

		static void transform(uint32_t digest[], uint32_t block[BLOCK_INTS], uint64_t &transforms)
		{
			/* Copy digest[] to working vars */
			uint32_t a = digest[0];
			uint32_t b = digest[1];
			uint32_t c = digest[2];
			uint32_t d = digest[3];
			uint32_t e = digest[4];

			/* 4 rounds of 20 operations each. Loop unrolled. */
			R0(block, a, b, c, d, e, 0);
			R0(block, e, a, b, c, d, 1);
			R0(block, d, e, a, b, c, 2);
			R0(block, c, d, e, a, b, 3);
			R0(block, b, c, d, e, a, 4);
			R0(block, a, b, c, d, e, 5);
			R0(block, e, a, b, c, d, 6);
			R0(block, d, e, a, b, c, 7);
			R0(block, c, d, e, a, b, 8);
			R0(block, b, c, d, e, a, 9);
			R0(block, a, b, c, d, e, 10);
			R0(block, e, a, b, c, d, 11);
			R0(block, d, e, a, b, c, 12);
			R0(block, c, d, e, a, b, 13);
			R0(block, b, c, d, e, a, 14);
			R0(block, a, b, c, d, e, 15);
			R1(block, e, a, b, c, d, 0);
			R1(block, d, e, a, b, c, 1);
			R1(block, c, d, e, a, b, 2);
			R1(block, b, c, d, e, a, 3);
			R2(block, a, b, c, d, e, 4);
			R2(block, e, a, b, c, d, 5);
			R2(block, d, e, a, b, c, 6);
			R2(block, c, d, e, a, b, 7);
			R2(block, b, c, d, e, a, 8);
			R2(block, a, b, c, d, e, 9);
			R2(block, e, a, b, c, d, 10);
			R2(block, d, e, a, b, c, 11);
			R2(block, c, d, e, a, b, 12);
			R2(block, b, c, d, e, a, 13);
			R2(block, a, b, c, d, e, 14);
			R2(block, e, a, b, c, d, 15);
			R2(block, d, e, a, b, c, 0);
			R2(block, c, d, e, a, b, 1);
			R2(block, b, c, d, e, a, 2);
			R2(block, a, b, c, d, e, 3);
			R2(block, e, a, b, c, d, 4);
			R2(block, d, e, a, b, c, 5);
			R2(block, c, d, e, a, b, 6);
			R2(block, b, c, d, e, a, 7);
			R3(block, a, b, c, d, e, 8);
			R3(block, e, a, b, c, d, 9);
			R3(block, d, e, a, b, c, 10);
			R3(block, c, d, e, a, b, 11);
			R3(block, b, c, d, e, a, 12);
			R3(block, a, b, c, d, e, 13);
			R3(block, e, a, b, c, d, 14);
			R3(block, d, e, a, b, c, 15);
			R3(block, c, d, e, a, b, 0);
			R3(block, b, c, d, e, a, 1);
			R3(block, a, b, c, d, e, 2);
			R3(block, e, a, b, c, d, 3);
			R3(block, d, e, a, b, c, 4);
			R3(block, c, d, e, a, b, 5);
			R3(block, b, c, d, e, a, 6);
			R3(block, a, b, c, d, e, 7);
			R3(block, e, a, b, c, d, 8);
			R3(block, d, e, a, b, c, 9);
			R3(block, c, d, e, a, b, 10);
			R3(block, b, c, d, e, a, 11);
			R4(block, a, b, c, d, e, 12);
			R4(block, e, a, b, c, d, 13);
			R4(block, d, e, a, b, c, 14);
			R4(block, c, d, e, a, b, 15);
			R4(block, b, c, d, e, a, 0);
			R4(block, a, b, c, d, e, 1);
			R4(block, e, a, b, c, d, 2);
			R4(block, d, e, a, b, c, 3);
			R4(block, c, d, e, a, b, 4);
			R4(block, b, c, d, e, a, 5);
			R4(block, a, b, c, d, e, 6);
			R4(block, e, a, b, c, d, 7);
			R4(block, d, e, a, b, c, 8);
			R4(block, c, d, e, a, b, 9);
			R4(block, b, c, d, e, a, 10);
			R4(block, a, b, c, d, e, 11);
			R4(block, e, a, b, c, d, 12);
			R4(block, d, e, a, b, c, 13);
			R4(block, c, d, e, a, b, 14);
			R4(block, b, c, d, e, a, 15);

			/* Add the working vars back into digest[] */
			digest[0] += a;
			digest[1] += b;
			digest[2] += c;
			digest[3] += d;
			digest[4] += e;

			/* Count the number of transformations */
			transforms++;
		}

		static void buffer_to_block(const std::string &buffer, uint32_t block[BLOCK_INTS])
		{
			/* Convert the std::string (byte buffer) to a uint32_t array (MSB) */
			for (size_t i = 0; i < BLOCK_INTS; i++)
			{
				block[i] = (buffer[4 * i + 3] & 0xff)
					| (buffer[4 * i + 2] & 0xff) << 8
					| (buffer[4 * i + 1] & 0xff) << 16
					| (buffer[4 * i + 0] & 0xff) << 24;
			}
		}

		SHA1::SHA1() {
			reset(this->digest, this->buffer, this->transforms);
		}

		void SHA1::update(const ::std::string &str) {
			::std::istringstream inputStream(str);
			this->update(inputStream);
		}

		void SHA1::update(::std::istream &inputStream) {
			while (true) {
				char sbuf[BLOCK_BYTES];

				inputStream.read(sbuf, BLOCK_BYTES - this->buffer.size());

				this->buffer.append(sbuf, inputStream.gcount());
				if (this->buffer.size() != BLOCK_BYTES)
					return;

				::std::uint32_t block[BLOCK_INTS];
				buffer_to_block(this->buffer, block);
				
				transform(this->digest, block, this->transforms);

				this->buffer.clear();
			}
		}

		::std::string SHA1::final() {
			/* Total number of hashed bits */
			::std::uint64_t total_bits = (this->transforms * BLOCK_BYTES + this->buffer.size()) * 8;

			/* Padding */
			this->buffer += 0x80;
			::std::size_t orig_size = this->buffer.size();
			while (this->buffer.size() < BLOCK_BYTES) {
				this->buffer += (char)0x00;
			}

			::std::uint32_t block[BLOCK_INTS];
			buffer_to_block(this->buffer, block);

			if (orig_size > BLOCK_BYTES - 8) {
				transform(this->digest, block, this->transforms);

				for (::std::size_t i = 0; i < BLOCK_INTS - 2; i++) {
					block[i] = 0;
				}
			}

			/* Append total_bits, split this uint64_t into two uint32_t */
			block[BLOCK_INTS - 1] = total_bits;
			block[BLOCK_INTS - 2] = (total_bits >> 32);
			transform(this->digest, block, this->transforms);

			/* Hex std::string */
			::std::ostringstream result;
			for (::std::size_t i = 0; i < sizeof(this->digest) / sizeof(this->digest[0]); i++) {
				result << ::std::hex << ::std::setfill('0') << ::std::setw(8);
				result << this->digest[i];
			}

			/* Reset for next run */
			reset(this->digest, buffer, transforms);

			return result.str();
		}


		::std::string SHA1::hashFile(const ::std::string &fileName) {
			::std::ifstream stream(fileName.c_str(), ::std::ios::binary);

			SHA1 checksum;
			checksum.update(stream);

			return checksum.final();
		}
	}
}