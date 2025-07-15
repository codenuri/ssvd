#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
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
	while (true )
	{
		TASK task;
		{
			std::unique_lock<std::mutex> ul(m);

			cv.wait( ul, [](){ return !Q.empty() || stop; });
				// => Q에 작업이 없고, stop ==true 가 아닌 경우만 대기 
				// => "pool 에 있는 스레드가 작업을 대기" 라는 표현이 위 코드 입니다.
			
			// pool 을 종료하라고 설정되고, Q가 비었다면 현재 스레드 종료(pool 스레드 종료)
			// => 작업이 남아도 "강제 종료" 하려면 Q.empty() 조사 부분 제거
			if ( stop == true && Q.empty() ) 
				return;				

			// 이제 Q에서 작업을 꺼내서 
			task = Q.front();
			Q.pop();
		}

		task(); // 작업 실행...
	}
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
		Q.push( task );	// 작업큐에 작업을 넣고
	}
	cv.notify_one(); // pool 에서 대기중인 스레드 중에서 한개만 깨웁니다.
}


int main()
{
	pool_init(4); // 4개의 스레드를 가지는 pool 생성. 

	// 이제 스레드로 수행할 작업이 필요하면 pool 에 작업을 넣으면 됩니다.
	pool_add(&foo); 
	pool_add(&foo); 
	pool_add(&foo); 
	pool_add(&foo); // <== 여기 까지 4개가 동시 실행

	pool_add(&foo); // <== 이후는 위 스레드중 먼저 작업을 종료한
	pool_add(&foo); //     스레드가 실행

	getchar(); // 주스레드 종료 방지!!
}



void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(1s);
	}
}
