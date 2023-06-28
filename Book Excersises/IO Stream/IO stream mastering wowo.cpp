#include <iostream>
#include <vector>
#include "C10.h"
#include "C11.h"

using namespace std;

int main()
{
    string sentence = "Two cats, and three cows";

    auto splitvec = split(sentence);
    auto splitvec2 = split(sentence, "Taeo,");

    for (string& i : splitvec)
        cout << i << "\n";

    cout << "\n\n";

    for (string& i : splitvec2)
        cout << i << "\n";

}


//Old code in main

/*
    TextToBinary("Text.txt", "binText");

    BinaryToText("binText", "BinToText.txt");

    multi_input();

    auto result = FindWord("c11text.txt", "siema");

    for (auto& i : result)
        cout << i << "\n";


    tolower("c11text.txt", "c11texttoloweroutput.txt");


    try
    {
    NumeroUno();
    Create_Readings();
    auto readings = Load_Readings("readings.txt");
    Print_Vector(readings);
    }
    catch (exception& e)
    {
        cout <<"\n"<< e.what() << "\n";
    }
    catch (...)
    {
        cout << "\nAn unexpected exception...\n";
    }


        auto numbers=find_numbers_in_file("Text with numbers.txt");

    for (auto& i : numbers)
    {
        cout << i << "\n";
    }

*/