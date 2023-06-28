#include <iostream>
#include "exc1.h"
#include "Token Calculator.h"
#include "C6.h"
#include "C8.h"
#include "C9.h"

using namespace std;

int main()
{
    try
    {
        C9::Library library;

        library.add_book(C9::Book("4321-987-866-X", "Przygody Siemanczka", "Siemanczek", C9::Date(), C9::Book::Genre::Biography, false));
        library.add_book(C9::Book("4321-987-866-X", "Przygody Siemanczka", "Siemanczek", C9::Date(), C9::Book::Genre::Biography, false));
        library.add_book(C9::Book("4321-987-866-X", "Przygody Siemanczka", "Siemanczek", C9::Date(), C9::Book::Genre::Biography, false));

        library.add_patron(C9::Library::Patron("Stefan", 98765, 0));
        library.add_patron(C9::Library::Patron("Heniek", 98767, 20));

        library.borrow_book(C9::Library::Patron("Stefan", 98765, 0), C9::Book("4321-987-866-X", "Przygody Siemanczka", "Siemanczek", C9::Date(), C9::Book::Genre::Biography, false));
    }
    catch (exception& e)
    {
        cerr << e.what();
    }

}

//Old code in main


    //vector<int> FibNums = C8::Fibonacci(20);
    //C8::print(FibNums);
    //C8::swap_vector(FibNums);
    //C8::print(FibNums);
    //Run(token_stream);
    //NumberDistribution();

    /*
    try
    {
        CombinationPermutationProgram();
    }
    catch (exception& e)
    {
        cerr <<"Exception: "<< e.what()<<endl;
    }

    system("pause");
    */
    //Run();
