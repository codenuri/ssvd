#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std::literals;

std::queue<int> Q;

// #1. mutex 를 사용한 접근 동기화
std::mutex m;

// #2. Q 가 비었을때 대기하기 위해
std::condition_variable cv;
// bool ready_data = false; // 관례적으로 이런 변수를 사용하지만
							// 현재 예제는 필요 없습니다.
							// 조사시 "Q.empty()" 로 하면 됩니다.

void producer()
{
	while (true)
	{
		static int cnt = 0;
		{
			std::lock_guard<std::mutex> g(m);
			Q.push(++cnt);
			std::cout << "producer : " << cnt << std::endl;
		}
		cv.notify_one();
		if (cnt == 1000000) cnt = 0;

		std::this_thread::sleep_for(10ms); // 생산에 시간소요
	}	
}

void consume()
{
	while (true)
	{
		{
			std::unique_lock<std::mutex> ul(m);

			cv.wait(ul, [](){ return !Q.empty(); });

			int element = Q.front();
			Q.pop();
			std::cout << "\tconsume : " << element << ", current Q size : " << Q.size() << std::endl;
		}
	}
}

int main()
{
	std::jthread t1(producer);
	std::jthread t2(consume);
}
