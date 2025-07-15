#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>
#include <functional>
#include <memory> // 스마트 포인터

using namespace std::literals;

int foo(int, int);


class ThreadPool
{
//	using TASK = void(*)(); 
	using TASK = std::function<void()>;

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

	std::future<int> pool_add(int(*f)(int, int), int arg1, int arg2 )
	{
		// 이제 Q에는 함수주소 자체가 아니라
		// package_task 를 만들고, packaged_task 객체를 실행하는 람다 표현식이 저장되어야 합니다.
		// => 동적 메모리에 할당 하는데, 스마트 포인터로 관리
		auto task = std::make_shared<std::packaged_task<int()>>(std::bind(f, arg1, arg2));

		// 실행되지 않았지만 결과를 미리 꺼내서, 반환해 줄수 있습니다.
		std::future<int> ft = task->get_future(); 

		// task 를 실행하는 람다 표현식
		auto work = [task](){ (*task)();};

		{
			std::lock_guard<std::mutex> g(m);
			Q.push( work );
		}
		cv.notify_one(); 

		return ft;
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
	
	std::future<int> ft = tp.pool_add(&foo, 1, 2); // 결국 이코드는
					//    std::async(&foo, 1, 2);  // 와 거의 동일합니다.	
	

	int ret = ft.get();

	std::cout << "결과 : " << ret << std::endl;
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
