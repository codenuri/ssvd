#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>


std::queue<int> Q; 
std::mutex m;		// Q 의 접근 동기화를 위한 뮤텍스


void producer()
{
	while (true)
	{
		{
			std::lock_guard<std::mutex> g(m);

			static int cnt = 0;
			Q.push(++cnt);
			std::cout << "producer : " << cnt << std::endl;
		}
		if (cnt == 1000000) cnt = 0;
	}	
}

void consume()
{
	while (true)
	{
		{
			std::lock_guard<std::mutex> g(m);
			int element = Q.front();
			Q.pop();
			std::cout << "\tconsume : " << element << ", current Q size : " << Q.size() << std::endl;
		}
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consume);

	t1.join();
	t2.join();
}
