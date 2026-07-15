#include <iostream>
#include <mutex>
#include <latch>
#include <thread>

std::latch sync_point{ 3 }; 

void foo(std::string name)
{
	std::cout << "start  work : " << name << std::endl;
	std::cout << "finish work : " << name << std::endl;

//	sync_point.count_down();	 // --count 기능
	sync_point.arrive_and_wait(); // --count 하고 count == 0 이 될때까지 대기 
								 // 즉, 일찍 도착 한 스레드는 다른 스레드가 이 위치에 올때 까지 대기후
								 // 모두 도착하면 다시 모두 실행시작

	std::cout << "have dinner : " << name << std::endl;
}

int main()
{
	std::jthread t1(foo, "kim"), t2(foo, "lee"), t3(foo, "park");

}
