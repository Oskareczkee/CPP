#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

//chapter 25
//12
namespace TEA
{
	void encipher(const unsigned long* const v,
				 unsigned long* const w,
				 const unsigned long* const k)
	{
		static_assert(sizeof(long) == 4, "Wrong size of the long word for TEA");
		
		unsigned long y = v[0];
		unsigned long z = v[1];
		unsigned long sum = 0;
		const unsigned long delta = 0x9E3779B9;

		for (unsigned long n = 32; n-- > 0;)
		{
			y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
			sum += delta;
			z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		}

		w[0] = y;
		w[1] = z;
	}

	void decipher(const unsigned long* const v,
				  unsigned long* const w,
				  const unsigned long* const k)
	{
		unsigned long y = v[0];
		unsigned long z = v[1];
		unsigned long sum = 0xC6EF3720;
		const unsigned long delta = 0x9E3779B9;

		static_assert(sizeof(long) == 4, "Wrong size of the long word for TEA");

		for (unsigned long n = 32; n-- > 0;)
		{
			z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
			sum -= delta;
			y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		}
		w[0] = y;
		w[1] = z;
	}
}

void decipher(const std::string& input_file_name, const std::string& output_file_name, std::string key)
{
	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	while (key.size() < kchar)
		key += '0';

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	std::ifstream ifs{ input_file_name };
	std::ofstream ofs{ output_file_name };

	if (!ifs || !ofs) throw std::exception("Wrong file name!");

	unsigned long inptr[2];
	char outbuf[nchar + 1];
	outbuf[nchar] = 0;

	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);

	ifs.setf(std::ios_base::hex, std::ios_base::basefield);

	while (ifs >> inptr[0] >> inptr[1])
	{
		TEA::decipher(inptr, outptr, k);
		ofs<<outbuf;
	}
}

void encipher(const std::string& input_file_name, const std::string& output_file_name, std::string key)
{
	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	while (key.size() < kchar)
		key += '0';

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	std::ifstream ifs{ input_file_name };
	std::ofstream ofs{ output_file_name };

	if (!ifs || !ofs) throw std::exception("Wrong file name!");

	unsigned long outptr[2];
	char inbuf[nchar];

	unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);

	int count = 0;

	while (ifs.get(inbuf[count]))
	{
		ofs << std::hex;

		if (++count == nchar)
		{
			TEA::encipher(inptr, outptr, k);
			ofs << std::setw(8) << std::setfill('0') << outptr[0] << ' ' << std::setw(8) << std::setfill('0') << outptr[1] << ' ';
			count = 0;
		}
	}

		if (count)
		{
			while (count != nchar) inbuf[count++] = '0';
			TEA::encipher(inptr, outptr, k);
			ofs << outptr[0] << ' ' << outptr[1] << ' ';
		}
}
