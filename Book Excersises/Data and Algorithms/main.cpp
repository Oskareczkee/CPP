#pragma once
#include <iostream>
#include <vector>
#include <list>
//#include "Containers and Iterators.h"
//#include "Templates.h"
#include "Maps and algorithms.h"
#include "CrackTimer.h"
#include <fstream>

using namespace std;


int main()
{
    try
    {
       //OrderTest();
        ofstream ArticleFreq{ "Article1 clean frequency.txt" };
        ifstream ArticleClean{ "Article1 clean.txt" };

        CleanFile("Article1.txt", "Article1 clean.txt");
        word_frequency(ArticleClean, ArticleFreq);
    }
    catch (exception& e)
    {
        cerr << e.what() << "\n";
    }
}


