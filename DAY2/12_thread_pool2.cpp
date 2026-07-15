#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();
//---------------------------------------------------
using TASK = void(*)(); // 작업은 결국 "함수 포인터"

std::queue<TASK> Q;     // 작업큐(함수 포인터를 담는 큐)

std::mutex m;				// 동시접근 제어
std::condition_variable cv; // Q 에 작업이 없으면 대기

bool stop = false;  // pool 을 종료하기 위한 flag

std::vector<std::thread> v; // pool 에 있는 N개의 스레드 관리
//-----------------------------------------------------------
// Q에 작업을 넣는 함수
void pool_add_work(TASK task)
{
	{
		std::lock_guard<std::mutex> g(m);
		Q.push(task);
	}
	cv.notify_one();
}

int main()
{
	// 스레드 풀에 4개의 작업을 넣는 코드
	Q.pool_add_work(foo);
	Q.pool_add_work(foo);
	Q.pool_add_work(foo);
	Q.pool_add_work(foo);
}

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
