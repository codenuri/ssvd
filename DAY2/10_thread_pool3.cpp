#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std::literals;

void foo();


class ThreadPool
{
	using TASK = void(*)(); 
	std::queue<TASK> Q; 

	std::mutex m;		
	std::condition_variable cv;	

	bool stop = false; 
	std::vector<std::thread> v; 
public:
	ThreadPool(int cnt)
	{
		for( int i= 0; i < cnt; i++)
		{
			// pool_thread_main : 멤버 함수 이므로 "객체.pool_thread_main()" 으로 호출해야 하는데
			//					  아래 처럼 호출하면 안됩니다.
			// v.push_back( std::thread( pool_thread_main));
			
			// 아래 처럼 해야 합니다(어제 2교시 배운 코드)
			v.push_back( std::thread( &ThreadPool::pool_thread_main, this));
		}
	}

	void pool_thread_main()
	{
		while (true )
		{
			TASK task;
			{
				std::unique_lock<std::mutex> ul(m);

				cv.wait( ul, [this](){ return !Q.empty() || stop; });					
				if ( stop == true && Q.empty() ) 
					return;				
				
				task = Q.front();
				Q.pop();
			}

			task(); 
		}
	}

	void pool_add(TASK task)
	{
		{
			std::lock_guard<std::mutex> g(m);
			Q.push( task );
		}
		cv.notify_one(); 
	}

	~ThreadPool()
	{
		{
			std::lock_guard<std::mutex> g(m);
			stop = true;
		}
		cv.notify_all(); // pool 의 모든 스레드를 깨우고

		// 안전하게 종료될때 까지 대기
		for( auto& t : v)
			t.join();
	}
};

int main()
{
	ThreadPool tp(4);
	
	tp.pool_add(&foo); 
	tp.pool_add(&foo); 
	tp.pool_add(&foo); 
	tp.pool_add(&foo);

	tp.pool_add(&foo);
	tp.pool_add(&foo);	
}	// <== tp 파괴. 소멸자 호출
	// <== pool 안에서 수행중인 스레드를 종료시키면 됩니다.



void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(1s);
	}
}

// 위 구현의 단점(한계점)
// => pool 에 넣을수 있는 함수 모양이 정해져 있다. (인자 있는 함수를 전달할수 없다.)
// => 함수의 반환값을 받을수 없다.
//       => 작업이 Q에 대기하다 실행되므로, 언제 실행할지 알수 없다.
//       => 하지만 미래의 결과를 담는 "std::future" 를 사용하면 미리 결과를 담은 객체를 얻고
//			ft.get() 으로 꺼내 면 된다.

