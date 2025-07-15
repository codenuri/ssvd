#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std::literals;

std::queue<int> Q; 
std::mutex m;	

std::condition_variable cv; // Q 가 비었을때 대기하기 위한 조건변수
// bool is_empty = false;   // 현재 예제는 이런 변수가 없어도 됩니다.
							// Q.is_empty() 로 조사하면 됩니다.
							// cv.wait(ul, [](){ return !Q.empty();}) 로 하면 됩니다.


void producer()
{
	while (true)
	{
		static int cnt = 0;
		
		std::this_thread::sleep_for(1ms); 
		{
			std::lock_guard<std::mutex> g(m);
			Q.push(++cnt);
			std::cout << "producer : " << cnt << std::endl;
		}
		cv.notify_all();

		if (cnt == 1000000) cnt = 0;
	}	
}

void consume()
{
	while (true)
	{
		{
			// #1. condition_variable 을 사용하려면 unique_lock 필요
			// std::lock_guard<std::mutex> g(m);
			std::unique_lock<std::mutex> ul(m);

			cv.wait(ul, []() { return !Q.empty(); } );


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
