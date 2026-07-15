#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
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

	void ThreadPool(int cnt)
	{
		for(int i = 0; i < cnt; i++)
		{
			v.emplace_back( thread_main );
		}
	}

	void add(TASK task)
	{
		{
			std::lock_guard<std::mutex> g(m);
			Q.push(task);
		}
		cv.notify_one();
	}


	void thread_main()
	{
		while(true)
		{
			TASK task;
			{
				std::unique_lock<std::mutex> ul(m);
				
				cv.wait(ul, []() { return !Q.empty() || stop; } );

				if ( stop == true && Q.empty() )
					break;
				
				task = Q.front();
				Q.pop();
			}
			task(); 
		}
	}

};


int main()
{	
	ThreadPool pool(4);
	
	pool.add(foo);
	pool.add(foo);
	pool.add(foo);
	pool.add(foo);

	getchar(); 
}

void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
