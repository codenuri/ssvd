#include <iostream>
#include <string_view>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::atomic<bool> use_flag = false;

// 아래 코드는 memory_order 를 지정해서 최적화
void work(std::string_view name)
{	
	while(use_flag.exchange(true, std::memory_order_acquire));

	std::cout << "using shared resource " << name << std::endl;

	//use_flag = false;	
	use_flag.store(false, std::memory_order_release);
}




int main()
{
	std::jthread t1(work, "A");
	std::jthread t2(work, "B");
	std::jthread t3(work, "C");

}