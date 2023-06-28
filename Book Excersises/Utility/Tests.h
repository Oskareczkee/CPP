#pragma once
#include <vector>
#include <iostream>
#include "BSTTree.h"
#include "CrackTimer.h"

using namespace std;

void TimerTest()
{
	CrackTimer Timer;

	Timer.StartTimer();
	Timer.EndTimer();
	double time=Timer.ShowTime(CrackTimer::TimeUnit::NANOSECONDS);
	Timer.ZeroTimer();
	cout << "\n";
	cout << time;
	cout << "\n\n" << Timer.ReturnCallendarTimeString();
}


class hehe
{
public:
	string heh;
	int dx;
	hehe(string x, int d) : heh(x), dx(d) {};
	hehe() {};
	bool operator >(const hehe& b)const { return this->heh > b.heh; };
	bool operator <(const hehe& b)const { return this->heh < b.heh; };
	//bool operator =(const int* b) { this->heh = ""; this->dx = 0; return true; };
};

int Comparator(hehe a, hehe b)
{
	if (a.heh > b.heh)return 1;
	if (a.heh < b.heh)return -1;
	return 0;
}

void Test()
{
	//BSTTree<int, int>::Node Node;
	string mess[10] = { "hej", "siema", "alalla", "matko jedyna", "Ojoj", "Bekas", "Cecylia", "Dinozaur", "ETeach", "Figa" };


	BSTTree<hehe> Tree;
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);
	Tree.Insert(hehe("x", 11), Comparator);



	/*
 BSTTree<int> Tree;
 //for(string str : mess)
	Tree.Insert(0);
	Tree.Insert(1);
	Tree.Insert(2);
	Tree.Insert(3);
	Tree.Insert(4);
	*/

	//int* Arr = NULL;
	cout << Tree.GetSize();
	//cout << &Tree.Root<<"\n"<<&Tree.HelperRoot;
	//Arr=Tree.GetContent();

	hehe hehi = Tree.Find(hehe("x", 11))->Data;
	Tree.Remove(hehe("x", 11));
	hehe* hehih = Tree.GetContent();

	cout << hehih[0].heh << hehih[1].heh << "\n";

	cout << "\n\n" << hehi.heh;
	cout << Tree.GetSize();

	//cout << Arr[0];
}


class A
{
public:
	class B
	{
	public:
		B() { cout << "B class constructor\n"; };
	};
	A() { cout << "A class constructor\n"; };
};