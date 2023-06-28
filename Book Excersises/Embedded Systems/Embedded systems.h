#pragma once
#include <bitset>
#include <iostream>
#include "CrackTimer.h"

using namespace std;

//Excersises 2, 4, 5 were to easy to write functions for them in here, you can find them in old code numerated

//6
void print_hex(int left, int right)//<left, right>
{
	for (int x = left; x <= right; x++)
		cout <<hex<<x<<" ";
}

//7
void print_chars()//keyboard chars
{
	//space=32, start from space, end at delete (127)
	for (char x = 32; x < 127; ++x)
		cout << x;
}

//8
//this function does not use any helper functions from libraries
void check_bytes_count()
{
	cout <<"int contains: "<<8 * sizeof(int)<<" bytes\n";

	//checks if char is signed
	char a = 'a';

	//+1 here, because range of signed values are <-val, val) <-128,128) for char
	//so we have to add +1 here, because opossite bites will have too low value 
	if ((int)(~a)+1 == (int)(-a))
		cout << "char is signed";
	else
		cout << "char is unsigned";
}


struct PPN
{
	PPN(unsigned int pfn, unsigned int cca, bool nreach, bool Dirty, bool Valid, bool Global)
		:PFN(pfn), CCA(cca), nonrechable(nreach), dirty(Dirty), valid(Valid), global(Global){}

	unsigned int PFN : 22;
	int : 3;
	unsigned int CCA : 3;
	bool nonrechable : 1;
	bool dirty : 1;
	bool valid : 1;
	bool global : 1;
};

template <size_t N>
void set_bits_in_range(const int& left, const int& right, bitset<N>& bits, string bitsstr)
{
	if (left < 0 || right > N || (right - left) != bitsstr.size())
		throw exception("set_bits_in_range: Bits out of range!");

	int index = 0;
	for (int i = left; i < right; ++i)
	{
		if (bitsstr[index] == '1')
			bits.set(i);
		else
			bits.reset(i);
		++index;
	}
}

//10
void usePPN()
{
	//using struct
	PPN ppn(20000, 4, false, false, false, false);

	cout << ppn.PFN << " " << ppn.CCA << " " << "flags: " << ppn.nonrechable << ppn.dirty << ppn.valid << ppn.global << "\n";

	//using bitset

	bitset<32> PPN;  //22 CCA, 3 PFN, 3 not used, 4 flags [bits]

	//PFN
	set_bits_in_range(10, 32, PPN, "0001000100010001000111");
	//CCA
	set_bits_in_range(4, 7, PPN, "111");
	//Flags
	set_bits_in_range(0, 4, PPN, "0000");

	cout << PPN;
}

void alloc_dealloc_check()
{
	const unsigned int object_size = 1000;
	const unsigned int object_count = 10000;

	CrackTimer timer1;

	timer1.StartTimer();
	bitset<object_size>* sets = new bitset<object_size>[object_count];
	timer1.EndTimer();

	CrackTimer timer2;
	timer2.StartTimer();
	delete[] sets;
	timer2.EndTimer();

	cout << "Alloc time: " << timer1.ShowTime(CrackTimer::TimeUnit::MILISECONDS) << "ms\n"
		<< "Dealloc time: " << timer2.ShowTime(CrackTimer::TimeUnit::MILISECONDS) << "ms\n";
}



