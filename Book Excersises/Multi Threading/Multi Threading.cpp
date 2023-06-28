#include <iostream>
#include <thread>
#include "Pointer to function.h"
#include "async.h"
#include "mutex.h"

using namespace std;

int main()
{
    srand(time(NULL));
    //PTF::Program();
    //Async::Program();
    Locks::LaunchProgram();
    cout << "hehej";
}

