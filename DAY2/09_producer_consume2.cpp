#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std::literals;

std::queue<int> Q; 
std::mutex m;		// Q 의 접근 동기화를 위한 뮤텍스

// 아래 코드는 mutex 로 접근 동기화를 하므로
// => 동시접근 문제는 해결했습니다.

// 남은 문제는
// => Q가 비었을때는 소비자는 대기 해야 합니다.
// => 생산자가 생산후에 소비 해야 합니다.



void producer()
{
	while (true)
	{
		static int cnt = 0;
		
		std::this_thread::sleep_for(1ms); // 지연
		{
			std::lock_guard<std::mutex> g(m);
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
