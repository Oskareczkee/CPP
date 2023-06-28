#pragma once
#include "C9.h"
#include <vector>

namespace C9
{
	const Date& DefaultDate()
	{
		static Date dd(2001, Month::jan, 1);
		return dd;
	}

	Date::Date(int Year, Month Month, int Day) : y(Year), m(Month), d(Day)
	{
	}

	Date::Date() : y(DefaultDate().year()), m(DefaultDate().month()), d(DefaultDate().day()) {}

	void Date::add_day(int amount)
	{

	}

	void Date::add_month(int amount)
	{

	}

	void Date::add_year(int amount)
	{
		if (m == Month::feb && d == 29 && !isLeapyear(y + amount))
		{
			m = Month::mar;
			d = 1;
		}
		y += amount;
	}

	bool Date::isDate(Date date)
	{
		Month m = date.month();
		int d = date.day();
		int y = date.year();

		if (d <= 0)return false;
		if (m < Month::jan||m>Month::dec)return false;
		
		//most of the months has 31 days
		int days_in_month = 31;

		switch (m)
		{
		case Month::feb:
			days_in_month = Date::isLeapyear(y) ? 29 : 28;
			break;

		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30;
			break;
		}

		if (d>days_in_month)return false;

		return true;

	}

	bool Date::isDate(int y, Month m, int d)
	{

		if (d <= 0)return false;
		if (m < Month::jan || m>Month::dec)return false;

		//most of the months has 31 days
		int days_in_month = 31;

		switch (m)
		{
		case Month::feb:
			days_in_month = Date::isLeapyear(y) ? 29 : 28;
			break;

		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30;
			break;
		}

		if (d > days_in_month)return false;

		return true;

	}

	bool Date::isLeapyear(int year)
	{
		return false;
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << "(" << d.year() <<","<< (int)d.month() << "," << d.day() << ")";
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char c1, c2, c3, c4;

		is >> c1 >> y >> c2 >> m >> c3 >> d >> c4;

		if (!is)return is;

		if (c1 != '(' || c2 != ',' || c3 != ',' || c4 != ')')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		dd = Date(y, Month(m), d);

		return is;
	}

	vector<string> split(string str, const char separator)
	{
		vector<string> result;
		int size = str.size();

		string token = "";

		for (int x = 0; x < size; x++)
		{
			if (str[x] != separator)
			{
				token += str[x];
				continue;
			}

			if (token != "")
			{
			result.push_back(token);
			token = "";
			}
		}

		//last token gets eaten, due the use of continue in loop, last token has to be added separately
		//this should be faster a little bit than checking if we are at the end of string in loop if statement, especially in long strings
		if (token != "")
		{
			result.push_back(token);
			token = "";
		}

		return result;
	}


	bool Book::checkISBN(const string& isbn)
	{
		auto tokens = split(isbn, '-');

		//n-n-n-x
		//n - number
		//x- integer or letter

		//there need to be 4 tokens
		if (tokens.size() != 4)
			return false;

		//first 3 tokens need to contain integers
		for (int x = 0; x < 3; ++x)
			if (tokens[x].find_first_not_of("0123456789") != string::npos)
				return false;

		//size of 4th token cannot be higher than 1 (it should contain only one character)
		if (tokens[3].size() != 1)
			return false;

		//if it has 1 char inside, get it
		char c = tokens[3][0];

		//check if this char is digit or letter
		if ((!isdigit(c)) && (!isalpha(c)))
			return false;

		//everything went ok !
		return true;

	}

	string GenreToString(const Book::Genre& genre)
	{
		switch (genre)
		{
		case C9::Book::Genre::None:
			return "";
		case C9::Book::Genre::Fiction:
			return "Fiction";
		case C9::Book::Genre::NonFiction:
			return "Non Fiction";
		case C9::Book::Genre::Magazine:
			return "Magazine";
		case C9::Book::Genre::Biography:
			return "Biography";
		case C9::Book::Genre::Children:
			return "Children";
		case C9::Book::Genre::Other:
			return "Other";
		default:
			return "Genre has not been defined, check genre enum";
		}
	}

	bool operator==(const Book& a, const Book& b)
	{
		return a.isbn() == b.isbn();
	}

	bool operator!=(const Book& a, const Book& b)
	{
		return !(a.isbn() == b.isbn());
	}

	ostream& operator<<(ostream& os, const Book& b)
	{
		//i wanted to show bool value of borrowed as string
		string isBorrowed="true";
		if (!b.isBorrowed())
			isBorrowed = "false";

		return os << "[ISBN] " << b.isbn() << "\n[Author] " << b.author() << "\n[Title] " << b.title() <<"\n[Genre] "<<GenreToString(b.genre()) << "\n[Copyright Date] " << b.copyright_date() << "\n[Borrowed] " << isBorrowed;
	}

	bool operator==(const Library::Patron& a, const Library::Patron& b)
	{
		return a.card_id() == b.card_id();
	}

	bool Library::FindPatron(const Patron& patron)
	{
		for (auto i : Patrons)
		{
			if (i == patron)
				return true;
		}
		return false;
	}

	bool Library::FindBook(const Book& book)
	{
		for (auto b : AvailableBooks)
			if (b == book)
				return true;
		return false;
	}

	void Library::borrow_book(const Patron& patron, const Book& book)
	{

		if (!FindBook(book))
			throw exception("Book has not been found !");
		if (!FindPatron(patron))
			throw exception("Patron has not been found !");

		if (patron.has_charges_to_pay())
			throw exception("Patron has charges to pay !");
		if (book.isBorrowed())
			throw exception("This book has been borrowed and is not available now !");

		Transaction transaction{book, patron, Date::Date() };

		Transactions.push_back(transaction);

	}

	void Library::patrons_with_charges_to_pay()
	{
		for (auto i : Patrons)
		{
			if (i.has_charges_to_pay())
				cout << i.name() << "\n";
		}
	}
}