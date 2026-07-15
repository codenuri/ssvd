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
//	using TASK = void(*)(); 			// 함수 주소만 보관 가능

	using TASK = std::function<void()>;	// 함수 주소, 람다 표현식, 멤버함수주소, 함수객체등...
										// 모두 보관 가능
										// 단 복사 가능한 타입만 가능한데
										// std::packaged_task 는 복사 안됨.. 따라서 직접보관못함
										// => 그래서 아래 코드에서는 람다 표현식 보관

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
			v.emplace_back( &ThreadPool::pool_thread_main, this);
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

	// [단점] : 인자가 2개인 함수만 등록가능
	// => 다음 소스에서 모두 해결
	std::future<int> pool_add(int(*f)(int, int), int arg1, int arg2 )
	{
		// #1. 인자 2개를 고정해서 std::packaged_task 객체로 생성
		// => "함수, 인자2개" => std::packaged_task 객체로 생성

		// 아래 코드는 지역변수 이므로 함수 종료시 파괴
		// std::packaged_task<int()> task(std::bind(f, arg1, arg2));

		// 파괴되지 않도록 하기위해 new 사용
		// => 언젠가 delete 되어야 하므로 불편하다.
		// auto task = new std::packaged_task<int()>((std::bind(f, arg1, arg2)));

		// 자동삭제를 지원하기 위해 "스마트 포인터" 도입
		auto task = std::make_shared<std::packaged_task<int()>>(std::bind(f, arg1, arg2));
		//-------------------------------------------------------
		
		// #2. 실행되지 않았지만 결과를 미리 꺼내서, 반환해 줄수 있습니다.
		std::future<int> ft = task->get_future(); 

		// #3. task 자체는 Q에 보관 안됨(std::function<> 에 담을수 없음)
		// => task 를 실행하는 람다 표현식
		auto work = [task](){ (*task)();};

		// #4. Q 에는 task 를 실행하는 람다 표현식을 보관
		{
			std::lock_guard<std::mutex> g(m);
			Q.push( work );
		}
		cv.notify_one(); 

		return ft;
	}
};

int main()
{
	ThreadPool tp(4);
	
	// pool 에 작업(함수) 등록시 바로 반환값 받을수 있습니다.
	std::future<int> ft = tp.pool_add(&foo, 1, 2); // 결국 이코드는
					//     std::async(&foo, 1, 2);  // 와 거의 동일합니다.	
	

	// pool 에 등록된 함수의 실행결과가 필요할때 아래 처럼
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
