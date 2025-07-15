#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

//---------------------------------------------------------
using TASK = void(*)(); // 작업은 함수 포인터

std::queue<TASK> Q; // 작업 큐(함수 포인터를 담는 큐)

std::mutex m;		// Q 접근 동기화
std::condition_variable cv;	// Q에 작업이 들어오면 signal

bool stop = false; // 스레드 풀 종료를 위한 flag
				   // stop = true 가 되면 모든 대기중인 스레드는 종료 되어야 한다.

std::vector<std::thread> v; // pool 에 있는 스레드 객체를 보관할 vector
//------------------------------------------------------------------------
// 아래 함수가 핵심 : pool 에 있는 스레드가 수행하게 되는 함수
void pool_thread_main()
{

}

void pool_init(int cnt)
{
	for( int i= 0; i < cnt; i++)
	{
		v.push_back( std::thread( pool_thread_main));
	}
}

// pool 에 작업을 추가하는 함수
void pool_add(TASK task)
{
	{
		std::lock_guard<std::mutex> g(m);
		Q.push_back( task );	// 작업큐에 작업을 넣고
	}
	cv.notify_one(); // pool 에서 대기중인 스레드 중에서 한개만 깨웁니다.
}


int main()
{
	pool_init(4); // 4개의 스레드를 가지는 pool 생성. 
}



void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
