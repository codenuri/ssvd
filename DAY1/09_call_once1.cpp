#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// init()
// => 시스템을 초기화 하는 함수
// => 최초 1회만 호출하면 되는 함수
void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

void foo()
{
    std::cout << "start foo" << std::endl;
    
	// 시스템을 초기화 하고
	init(10, 3.4);     

	// 주어진 역활을 수행 - 단, 이작업을 하기전에 반드시 시스템은 초기화 되어야 한다.

    std::cout << "finish foo" << std::endl;
}
int main()
{
    std::jthread t1(foo);
	std::jthread t2(foo);
	std::jthread t3(foo);
    
}



