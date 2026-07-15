#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

// 공유 자원 - STL 의 Q
// => STL 은 동기화 기능이 없습니다.
// => 멀티 스레드 환경에서 서로 다른 스레드간 공유해서 사용하면 오류 발생
// => 해결은 다음소스에서
std::queue<int> Q;

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
	std::jthread t1(producer);
	std::jthread t2(consume);
}
