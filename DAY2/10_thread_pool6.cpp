#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>
#include <functional>

using namespace std::literals;

int foo(int, int);


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
		cv.notify_all(); 
		for( auto& t : v)
			t.join();
	}
};

int main()
{
	ThreadPool tp(4);
	
	tp.pool_add(&foo, 1, 2); 
}	

int foo(int a, int b)
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(1s);
	}

	return a + b;
}
