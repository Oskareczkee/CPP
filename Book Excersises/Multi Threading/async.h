#pragma once
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace Async
{
    int ReturnValue(int value)
    {
        srand(time(NULL));
        return rand() % (100 - 50) + 50;
    }

    const int THREAD_NUM = 10;
    vector<future<int>> tasks;

    void Program()
    {


    for (int i = 0; i < THREAD_NUM; i++)
    {
        tasks.push_back(async(ReturnValue, 5));
    }

    int total=0;

    for (auto& t : tasks)
    {
        total += t.get();
    }

    cout << total;
    }

}