#include <iostream>
#include <mutex>
#include <latch>   // C++20
#include <barrier> // C++20
#include <thread>

//std::latch   sync_point{ 3 }; // 1회만 가능. 
std::barrier sync_point{ 3 }; // 여러번 사용가능

void foo(std::string name)
{
	std::cout << "start  work : " << name << std::endl;
	std::cout << "finish work : " << name << std::endl;


	sync_point.arrive_and_wait(); // --count 후 count == 0 대기
								  // count == 0 되면 count = 3 후에 실행시작
	std::cout << "have dinner : " << name << std::endl;


	sync_point.arrive_and_wait(); 
	std::cout << "go home : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"), t2(foo, "lee"), t3(foo, "park");

}
