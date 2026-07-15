#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

void foo();

// 아래 ThreadPool 은
// 1. std::mutex, std::condition_variable
// 2. std::vector<thread>
// 3. 멤버 함수를 스레드로 수행
// 4. thread pool 의 개념

// 을 잘 설명하는 코드 입니다.
// => 기본 학습용 thread pool 코드

// 문제점
// 1. pool 에 넣을수 있는 함수의 모양이 제한적 (인자 없는 함수만 가능. 인자 전달 못함)
// 2. 함수포인터만 보관, 람다 표현식등을 실행 안됨
// 3. pool 로 수행하는 함수는 반환값을 가질수 없다.(작업 모양이 void(*)() 이다 )
// => 해결할수 있지만 복잡해진다...
// => 다음 단계에서 해결.. 


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
		for(int i = 0; i < cnt; i++)
		{
//			v.emplace_back( thread_main ); // error
										   // thread_main 은 이제 "일반함수" 가 아닌 "멤버함수"	입니다.
										   // 객체 주소(this) 필요 합니다.

			v.emplace_back( &ThreadPool::thread_main, this ); // std::thread t(&ThreadPool::thread_main, this)							   
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
				
				cv.wait(ul, [this]() { return !Q.empty() || stop; } );

				if ( stop == true && Q.empty() )
					break;
				
				task = Q.front();
				Q.pop();
			}
			task(); 
		}
	}

	~ThreadPool()
	{
		// pool 을 중지
		{
			std::lock_guard<std::mutex> g(m);
			stop = true;
		}
		cv.notify_all(); // pool의 모든 스레드를 깨우고

		// 모든 스레드가 실제로 종료될때까지 대기
		for( auto& t : v) 
			t.join();
	}
};

int main()
{	
	ThreadPool pool(4);
	
	pool.add(foo);
	pool.add(foo);
	pool.add(foo);
	pool.add(foo);
} // <== pool 파괴. 소멸자 


void foo()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
}
