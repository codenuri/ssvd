#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;


//std::atomic<bool> wait_flag = false; // 환경에 따라 lock-free 일수도 있고 아닐수도 있습니다

// std::atomic_flag wait_flag;  		 // std::atomic<bool> 과 유사 하지만 항상 lock-free 를 보장 합니다.

std::atomic_flag wait_flag = ATOMIC_FLAG_INIT; // C++20 이전에는 이 초기화 필요
												// C++20 이후에는 초기화 필요 없음. 

void work()
{
	// 아래 A, B 도 동시에 되어야 합니다. 아래 처럼 만들면 버그.
//	while( wait_flag ); // A
//	wait_flag = true;   // B

	// 아래 코드가 위 코드와 같은데, lock-free 보장합니다
	while( wait_flag.test_and_set() );

	std::cout << "start. using shared resource" << std::endl;
	std::cout << "end.   using shared resource" << std::endl;

//	wait_flag = false;
	wait_flag.clear();
}

 
int main()
{
	std::thread t1(work), t2(work);

	t1.join();
	t2.join();
}