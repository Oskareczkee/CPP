#pragma once
#include<iostream>
#include<fstream>
#include "Templates.h"
#include<algorithm>
#include <set>
#include <map>
#include <iterator>
#include <sstream>
#include <numeric>

using namespace std;

namespace maa_test
{
	struct Item
	{
		string name;
		int iid{};
		double value{};
	};

	//name iid value\n
	istream& operator>>(istream& is, Item& it)
	{
		string n;
		int IID;
		double val;

		is >> n >> IID >> val;

		if (!is)
			return is;
		it = Item{ n, IID, val };
		return is;
	}

	ostream& operator<<(ostream& os, const Item& it)
	{
		return os << it.name << " " << it.iid << " " << it.value << "\n";
	}

	void test()
	{
		try
		{
			ifstream is{ "Items.txt" };

			vector<maa_test::Item> items;

			Item temp;
			while (is >> temp)
				items.push_back(temp);

			items.push_back(Item{ "horse shoe", 99, 12.34 });
			items.push_back(Item{ "Cannon S400", 9988, 499.95});
			/*
			auto it1 = find_if(items.begin(), items.end(), [](const Item& it) {return it.name == "DOOM"; });
			items.erase(it1);
			auto it2 = find_if(items.begin(), items.end(), [](const Item& it) {return it.name == "Cukierki"; });
			items.erase(it2);
			*/

			auto it1 = find_if(items.begin(), items.end(), [](const Item& it) {return it.iid == 1; });
			items.erase(it1);
			auto it2 = find_if(items.begin(), items.end(), [](const Item& it) {return it.iid == 3; });
			items.erase(it2);

			//sort(items.begin(), items.end(), [](const Item& i1, const Item& i2) {return i1.name < i2.name; });
			//sort(items.begin(), items.end(), [](const Item& i1, const Item& i2) {return i1.iid > i2.iid; });
			sort(items.begin(), items.end(), [](const Item& i1, const Item& i2) {return i1.value > i2.value; });


			for (auto& it : items)
			{
				cout << it;
			}
		}
		catch (exception& ex)
		{
			cerr << ex.what();
		}
	}
}

namespace overloaded_algorithms
{
	//3
template <class Iter, class T>
	requires input_iterator<Iter>&& equality_comparable<T>
int count(Iter beg, Iter end, const T& val)
{
	if (beg == end)
		return 0;

	int count = 0;
	while (beg != end)
	{
		if (*beg == val)
			++count;
		++beg;
	}
	return count;
}

	//4
template <class Iter, class Pred>
	requires input_iterator<Iter>
int count_if(Iter beg, Iter end, Pred predicate)
{
	if (beg == end)
		return 0;

	int c = 0;
	while (beg != end)
	{
		if (predicate(*beg))
			++c;
		++beg;
	}
	return c;
}

	//7
template<class Iter, class Val>
	requires input_iterator<Iter>
bool binary_search(Iter beg, Iter end, Val val)
{
	int count = distance(beg, end) / 2;

	if (*beg == val)
		return true;

	//when array have size of 8, its last index is 7, count will be 8 anywany, so we subtract 1 here
	advance(beg, count-1);
	while (count > 0)
	{
		count /= 2;
		if (*beg == val)
			return true;
		else if (*beg > val)
			advance(beg, -count);
		else
			advance(beg, count);
	}
	return false;

}

}

//6
struct Fruit
{
	string name;
	int count;
	double unit_price;
};

struct Fruit_comparsion
{
	bool operator()(const Fruit* a, const Fruit* b)const { return a->name < b->name; }
};
void t6()
{
	set < Fruit*, Fruit_comparsion> fruit_set;

	fruit_set.insert(new Fruit{ "Japko!!!!!!", 30, 1.20 });
	fruit_set.insert(new Fruit{ "Winogrona", 20, 2.20 });
	fruit_set.insert(new Fruit{ "Mandarynki", 10, 3.20 });
	fruit_set.insert(new Fruit{ "Banany", 40, 3.50 });

	for (auto& x : fruit_set)
		cout << x->name<<"\n";
}

void word_frequency(istream& is = cin, ostream& output=cout)
{
	map<string, int> words;
	list<pair<int, string>> lst;

	for (string s; is >> s;)
		++words[s];

	
	for (const auto& p : words)
		cout << p.first << " " << p.second << "\n";

	for (auto& p : words)
		lst.emplace_back(pair<int, string>(p.second, p.first));

	lst.sort([](pair<int, string> p1, pair<int, string> p2) {return p1.first > p2.first; });

	cout << "\n\n";
	for (auto& p : lst)
		output << p.first << " " << p.second << "\n";

}

//9
struct Purchase
{
	string name;
	double unit_price;
	int count;
};

//Format:
//name unit_price count
istream& operator>>(istream& is, Purchase& pur)
{
	string name;
	double unit_price;
	int count;

	is >> name >> unit_price >> count;

	if (!is)
		return is;

	pur = Purchase{ name, unit_price, count };

	return is;
}

ostream& operator<<(ostream& os, const Purchase& pur)
{
	return os << pur.name << "  " << pur.unit_price << "  " << pur.count << "\n";
}

struct Order
{
	string name;
	string address;
	string date;
	vector<Purchase> purchases;

bool operator < (const Order& src) const
	{
		return name < src.name;
	}
};

//Format:
// 'line'
//name address comment
//purchase data
//purchase data
//...
// 'line'
istream& operator>>(istream& is, Order& ord)
{
	string name, address, date;
	vector<Purchase> purchases;
	string line1;

	getline(is, line1);

	istringstream sst{ line1 };

	sst >> name >> address >> date;

	if (!sst)
		return is;

	string line;
	while (getline(is, line) && !line.empty())
	{
		istringstream ss{ line };
		Purchase p;

		if (ss >> p)
			purchases.push_back(p);
	}

	ord = Order{ name, address, date, purchases };

	return is;
}

ostream& operator<<(ostream& os, const Order& ord)
{
	ostringstream oss{ string() };

	oss << "Name: " << ord.name << "  Address: " << ord.address << "  Date: " << ord.date << "\n\n";
	oss << "Purchases:\n{\n";
	for (auto& p : ord.purchases)
		oss << p;
	oss << "}\n\n";

	return os << oss.str();
}

void OrderTest()
{
	ifstream is{ "Orders.txt" };
	vector<Order> orders;

	Order temp;
	while (is >> temp)
		orders.push_back(temp);

	//for (auto& p : orders)
		//cout << p;

	vector<Order> ordercpy(orders.size());
	copy(orders.begin(), orders.end(), ordercpy.begin());
	//sort(orders.begin(), orders.end(), [](const Order& ord1, const Order& ord2) {return ord1.name < ord2.name; });
	sort(orders.begin(), orders.end(), [](const Order& ord1, const Order& ord2) {return ord1.address < ord2.address; });
	for (auto& p : orders)
		cout << p;

	//orders sorted by address
	
	/*
	ofstream orderAddress{"OrdersByAddress.txt"};

	for (auto& p : orders)
		orderAddress << p;
	*/
	vector<Order>ordersMerged(orders.size()+ordercpy.size());

	sort(orders.begin(), orders.end());
	sort(ordercpy.begin(), ordercpy.end());

	merge(orders.begin(), orders.end(), ordercpy.begin(), ordercpy.end(), ordersMerged.begin());

	
	ofstream MergedOrders{ "OrdersMerged.txt" };
	for (auto& p : ordersMerged)
		MergedOrders << p;
}

//10
void AccumulateOrders()
{
	vector<Order> orders;

	ifstream ifs1{ "OrdersMerged.txt" };
	ifstream ifs2{ "OrdersByAddress.txt" };

	Order temp;
	while (ifs1 >> temp)
		orders.push_back(temp);

	while (ifs2 >> temp)
		orders.push_back(temp);

	//I literally don't know if it outputs right answser XD, too big values, to test this
	//EDIT: It looks like it works XD
	cout << "\n\n" << accumulate(orders.begin(), orders.end(), 0, [](int i, Order& o2)
		{
			for (auto& p : o2.purchases)
				i +=p.count * p.unit_price;
			return i;
		}
	);

	int sum = 0;

	for (auto& p : orders)
		for (auto& s : p.purchases)
			sum += s.count * s.unit_price;
	cout <<"\n"<< sum;
}

//13
//without converting plurals and abbreviations
int punctuationToSpace(int C)
{
	static const int SPACE = 32;

	//idk why, but i had to use iswpunct here XD
	if (iswpunct(C))
		C = SPACE;
	return C;
}

//returns copy of processed string
string processString(const string& str)
{
	istringstream iss{ str };
	ostringstream oss{ string() };

	string temp;
	while (iss >> temp)
	{
		//change all big letters to small
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		//change all punctuation to space
		transform(temp.begin(), temp.end(), temp.begin(), ::punctuationToSpace);

		oss << temp<<" ";
	}

	return oss.str();
}

void CleanFile(const string& fileName, const string& outputFile)
{
	ifstream ifs{ fileName };
	ofstream ofs{ outputFile };
	if (!ifs)
		throw exception("Wrong file name !");

	string temp;
	//getline to catch newline characters
	while (getline(ifs, temp, '\n'))
	{
		temp = processString(temp);
		ofs << temp<<"\n";
	}
}