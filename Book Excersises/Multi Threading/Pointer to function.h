#pragma once
#include <iostream>
#include <thread>

using namespace std;

namespace PTF
{

//#define THREAD_NUM 5

void Log(string text)
{
	cout << text << "\n";
}

void Program()
{
	thread threadArr[] = {thread(Log, "siema"),  
	thread (Log, "no hejka co tam"),
	thread (Log, "elo"),
	thread (Log, "uouo"),
	thread (Log, "nie wiem"),
	thread (Log, "aha eh"),	
	};

	for (thread& t : threadArr)
	{
		if (t.joinable())
			t.join();
	}

}

}

