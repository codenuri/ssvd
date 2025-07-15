#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// condition_variable 사용예제

std::queue<int> Q; // 전역변수 Q, 모든 스레드 공유.

// 현재 코드는 2개 이상의 스레드가 동기화 없이 Q 를 사용하면 
// => 비정상 종료 될수 있습니다.

void producer()
{
	while (true)
	{
		static int cnt = 0;
		Q.push(++cnt);
		std::cout << "producer : " << cnt << std::endl;
		if (cnt == 1000000) cnt = 0;
	}	
}

void consume()
{
	while (true)
	{
		int element = Q.front();
		Q.pop();
		std::cout << "\tconsume : " << element << ", current Q size : " << Q.size() << std::endl;
	}
}

int main()
{
	std::thread t1(producer);
	std::thread t2(consume);

	t1.join();
	t2.join();
}
