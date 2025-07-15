#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

using TASK = void(*)(); // 작업은 함수 포인터

std::queue<TASK> Q; // 작업 큐(함수 포인터를 담는 큐)

std::mutex m;		// Q 접근 동기화
std::condition_variable cv;	// Q에 작업이 들어오면 signal

bool stop = false; // 스레드 풀 종료를 위한 flag
				   // stop = true 가 되면 모든 대기중인 스레드는 종료 되어야 한다.






int main()
{
	while (true)
	{
		getchar();

		std::thread t(foo);
		t.detach();
	}
}

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
