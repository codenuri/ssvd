#include <iostream>
#include <mutex>
#include <thread>
#include <latch>

// latch : 카운트 기반에 간단한(가벼운) 동기화 도구, C++20 에서 추가 
std::latch mylatch(3); // 내부적으로 3을 보관

void foo(const std::string& name)
{
	std::cout << "start  work : " << name << std::endl;
	std::cout << "finish work : " << name << std::endl;

	// 업무 종료후 집에 퇴근전에 보고해야 한다
	mylatch.count_down(); // --count

	std::cout << "go home     : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"), t2(foo, "lee"), t3(foo, "park");

	// 모두 퇴근할때 까지 대기(모든 스레드가 특정 위치에 도달할때 까지 대기)
	mylatch.wait(); // count == 0 이 될때 까지 대기. 

	std::cout << "receive signal" << std::endl;
}
