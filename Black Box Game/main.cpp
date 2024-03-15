#include <iostream>
#include "Game.h"

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "en_US.utf8");
    std::locale loc("en_US.UTF-8");
    std::wcout.imbue(loc);


    BlackBoxGame game;
    game.Start();
}