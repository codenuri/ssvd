#include <iostream>
#include <string_view>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

// lock-free : CPU 의 명령만으로 동기화 보장, OS 기능 사용 안함

// std::atomic<bool>  : 환경에 따라 lock-free 일수도 있고, 아닐수도 있습니다.
//						lock-free 보장 안함

// std::atomic_flag   : std::atomic<bool> 과 유사하지만 lock-free 보장합니다
//						std::atomic<bool> 보다 기능은 적습니다.(lock-free 가능한  명령만제공)

// spin lock 만들때는 atomic_flag 선호!!

//std::atomic<bool> use_flag = false;

std::atomic_flag use_flag = ATOMIC_FLAG_INIT; // C++17 까지는 초기값 필요.
   										      // C++20 부터는 초기값 생략 가능

void work(std::string_view name)
{	
	// std::atomic_flag 는 spin 구현에 최적화 되어 있습니다. 
	// 따라서 "set", "clear()", "test()"
	while(use_flag.test_and_set());

	std::cout << "using shared resource " << name << std::endl;

	use_flag.clear();
}




int main()
{
	std::jthread t1(work, "A");
	std::jthread t2(work, "B");
	std::jthread t3(work, "C");

}