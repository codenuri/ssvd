#include <iostream>
#include <string_view>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

//bool use_flag = false;

std::atomic<bool> use_flag = false;

void work(std::string_view name)
{	
	// 아래 3가지 동작은 atomic 하게 처리 
	// 1. temp = use_flag;
	// 2. use_flag = true(1번째인자) 로 설정
	// 3. return temp
	// 아래 코드는 버그 없는 안전한 코드
	// 단, memory_order 지정 안했으므로 항상 seq_cst 입니다.
	while(use_flag.exchange(true));

	std::cout << "using shared resource " << name << std::endl;

	use_flag = false;	
}




int main()
{
	std::jthread t1(work, "A");
	std::jthread t2(work, "B");
	std::jthread t3(work, "C");

}