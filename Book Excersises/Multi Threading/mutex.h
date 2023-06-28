#pragma once

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include <cstdlib>

//mutex, shared_mutex
//unlock, lock
// 
// Lock Guardy - "typ locka"<mutex type> nazwa (referencja do naszego mutexa)
// 
//lock_guard - po stworzeniu blokuje dane, po zniszczeniu odblokowuje je. Dane da siê tylko odblokowaæ niszcz¹c obiekt
//unique_lock - to samo co lock_guard, ale mo¿na odblokowywaæ i zablokowywaæ sobie dane dowoli, po stworzeniu automatycznie blokuje dane
//shared_lock<shared_mutex> - tworzy critical section, ale wiele w¹tków mo¿e ich u¿ywaæ, najlepiej dawaæ je do blokowania operacji typu odczyt, do zapisu itd niezalecane, mo¿e powodowaæ b³êdy
//lock(mutex1, mutex2) - ta funkcja chroni przed deadlockiem, gdzie kilka w¹tków mo¿e czekaæ na siebie nawzajem, ale ka¿dy jest zablokowany, wiêc nigdy siê nie porozumiej¹
//                       Wywo³ujemy j¹ zawsze na pocz¹tku naszej funkcji, w której chcemy zaimplementowaæ multi-threading
//                       Po tej funkcji w konstuktorze lock guardów dajemy 2 argument "adopt_lock", który powoduje, ¿e po stworzeniu nasze mutexy nie s¹ od razu zablokowane, bo ju¿ raz je zablokowaliœmy funkcj¹ lock()
//scoped_lock - ten lock pozwala nam stworzyæ lock, który automatycznie wywo³uje za nas funkcjê lock i potem nie musimy tworzyæ dodatkowych guardów w kodzie, zostan¹ utworzone automatycznie
//              Odblokowuje guardy, poprzez ich zniszczenie (gdy wyjdziemy poza funkcjê lub pêtlê)
//
// condition_variable
// cv.notify_one - wysy³a powiadomienie  cv.notify_all - wysy³a powiadomienia do wszystkich czekaj¹cych w¹tków, zamiast do jednego
// cv.wait(mutex, predicate) - czeka na powiadomienie --- przyk³ad predykatu (lambda) [](){return zadanie_gotowe;} w skrócie, funkcja ta czeka a¿ zadanie_gotowe bêdzie ustawione na true
// Conditional variables pozwalaj¹ nam na porozumiewanie siê 2 funkcji w ró¿nych w¹tkach, musz¹ mieæ wspólnu lock(mutex), wtedy 1 funkcja mo¿e czekaæ na dane, które dla niej stworzy 2 funkcja
//


namespace Locks
{
	using namespace std;

    mutex g_mutex;
	bool g_ready = false;
	condition_variable g_cv;
	int G_Data;
	int Data_Counter = 0;
	const int Data_to_send = 10;
	bool g_end = false;

	int GetRandomValue()
	{
		return rand() % 10000 + 1;
	}
	void Producer()
	{
		while (!g_end)
		{
			unique_lock<mutex> lock(g_mutex);
			G_Data = GetRandomValue();
			Data_Counter++;

			g_ready = true;
			lock.unlock();
			g_cv.notify_one();
			lock.lock();
			if (Data_Counter == Data_to_send)
			{
				g_end = true;
			    g_cv.notify_one();
			}
			g_cv.wait(lock, [&](){return g_ready == false; });
		}
	}

	void Consumer()
	{
		int data = 0;
		while (!g_end)
		{
			unique_lock<mutex> lock(g_mutex);
			g_cv.wait(lock, [&]() {return g_ready; });
			data = G_Data;
			cout << data << " Has been transported successfull\n";
			g_ready = false;
			lock.unlock();
			if (g_end)
			{
				cout << "End";
			}
			g_cv.notify_one();
			lock.lock();
		}
	}
       void LaunchProgram()
		{
		   /*
			vector<thread> Producers= { thread(Producer), thread(Producer), thread(Producer) };
			vector<thread> Consumers;
			for (int x = 0; x < 5; x++)
				Consumers.push_back(thread(Consumer));
		   */

		   //Code above and below doesnt work, i don't know reason why
		   thread t1(Producer);
		   thread c1(Consumer);
		   t1.join();
		   c1.join();

			/*

			for (auto& t : Producers)
			{
				if(t.joinable())
				t.join();
			}
			for (auto& t : Consumers)
			{
				if (t.joinable())
				t.join();
			}
			*/
		}
}
