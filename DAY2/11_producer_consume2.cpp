#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>


std::queue<int> Q;

// 현재 코드는
// 뮤텍스를 사용한 접근 동기화는 해결
// 
// 그런데, 문제는
// => Q가 비었을때 소비하면 안됩니다.
// => Q가 비었을때는 생산자를 기다려야 합니다. 
// => 다음소스에서 해결

// #1. mutex 를 사용한 접근 동기화
std::mutex m;




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
	std::jthread t1(producer);
	std::jthread t2(consume);
}
