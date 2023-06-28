#include <iostream>
#include <fstream>
#include "CSSParser.h"
#include "list.h"
#include "myString.h"
#include "CommandHandler.h"

using namespace std;

//ifstream file{ "test.txt" };

int main()
{
    try
    {
        //CSSParser parser(file);
        //parsing through input stream
        CSSParser parser(cin);
        parser.Parse();

        //parser.PrintContent();
        CommandHandler cmd(parser);

        while (true)
        {
            if (!cin)
                break;
            cmd.GetCommand();
        }
    }
    catch (exception& e)
    {
        cerr << e.what();
    }
}

