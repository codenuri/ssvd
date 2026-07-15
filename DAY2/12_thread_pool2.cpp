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

// pool 초기화(스레드 생성)
void pool_init(int cnt)
{
	// std::vector<std::thread> v;

	for(int i = 0; i < cnt; i++)
	{
		v.emplace_back( pool_thread_main );
	}
}

// 아래 코드가 핵심 : pool 에 있는 모든 스레드가 수행하는 함수
void pool_thread_main()
{
	while(true)
	{
		{
			std::unique_lock<std::mutex> ul(m);
			
			// Q에 작업이 들어올때 까지 대기
			cv.wait(ul, []() { return !Q.empty(); } );
			
			// stop 변수가 설정되고, Q가 비었다면 pool 종료!!!
			// => pool종료하면 stop 변수 세팅후, cv.notify_all()
			if ( stop == true && Q.empty() )
				break;

			// Q에 놓인 작업 실행(첫번째 요소 꺼내서 호출)
			Task task = Q.front();
			Q.pop();
		}
		task(); // 작업실행
	}
}

int main()
{	
	pool_init(4); // pool에 4개의 스레드를 만들어 달라.

	// 스레드 풀에 4개의 작업을 넣는 코드
//	Q.pool_add_work(foo);
//	Q.pool_add_work(foo);
//	Q.pool_add_work(foo);
//	Q.pool_add_work(foo);
}

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
