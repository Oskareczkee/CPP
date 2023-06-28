#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace C9
{
	enum class Month{jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec};
	enum class Day{sunday, monday, tuesday, wednesday, thursday, friday, saturday};

	vector<string>split(string string, const char separator);

	class Date
	{
		private:
			int y;
			Month m;
			int d;
		public:
			class Invalid{};
			Date(int Year, Month Month, int Day);
			Date();

			//non-modifying
			int day()const { return d; }
			Month month()const { return m; }
			int year()const { return y; }

			//modyfing
			void add_day(int amount);
			void add_month(int amount);
			void add_year(int amount);

			static bool isDate(Date);
			static bool isDate(int y, Month m, int d);
			static bool isLeapyear(int year);
	};


	class Book
	{
	public:
		enum class Genre{None,Fiction, NonFiction, Magazine, Biography, Children, Other};


		string isbn()const { return ISBN; };
		string title()const  { return Title; };
		string author()const  { return Author; };
		Date copyright_date()const { return CopyrightDate; };
		Genre genre()const { return GenreType; };
		bool isBorrowed()const { return hasBeenBorrowed; };
		Book(string ISBNn, string Titlee, string Authorr, Date Date,Genre genre, bool hasBeenBorrowedd) : ISBN(ISBNn), Title(Titlee), Author(Authorr), CopyrightDate(Date),GenreType(genre), hasBeenBorrowed(hasBeenBorrowedd)
		{
			if (!checkISBN(ISBNn))throw Invalid();
		};
	private:
		struct Invalid { Invalid() { throw exception("ISBN format is invalid !"); } };
		bool checkISBN(const string& isbn);
	private:
		string ISBN;
		string Title;
		string Author;
		Date CopyrightDate;
		Genre GenreType;
		bool hasBeenBorrowed;
	};

	class Library
	{
	public:
		class Patron
		{
		private:
			string Name;
			long int cardID;
			int ChargesToPay;
		public:
			string name()const { return Name; }
			long int card_id()const { return cardID; }
			int charges_to_pay()const { return ChargesToPay; }
			bool has_charges_to_pay()const { if (ChargesToPay > 0)return true; return false; }
			void add_charge(int amount) { ChargesToPay += amount; }
			Patron(string name, long int cardid, int charges_to_pay) : Name(name), cardID(cardid), ChargesToPay(charges_to_pay) {};
		};

		struct Transaction
		{
			Book book;
			Patron patron;
			Date date;
		};

	private:
		vector<Book> AvailableBooks;
		vector<Patron> Patrons;
		vector<Transaction> Transactions;

		bool FindPatron(const Patron& patron);
		bool FindBook(const Book& book);

	public:
		void add_patron(Patron patron) { Patrons.push_back(patron); }
		void add_book(Book book) { AvailableBooks.push_back(book); }
		void borrow_book(const Patron& patron, const Book& book);
		void patrons_with_charges_to_pay();
	};


	string GenreToString(const Book::Genre& genre);


}
