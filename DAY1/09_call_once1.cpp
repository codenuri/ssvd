#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

// init : 시스템을 초기화 하는 함수.
//        최초 1회만 호출되면 됩니다.
void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

void foo()
{
    std::cout << "start foo" << std::endl;

    init(10, 3.4);     // 초기화

	// 주어진 역활 수행 - 반드시 초기화(init) 이 먼저 되어야 한다고 가정.

    std::cout << "finish foo" << std::endl;
}
int main()
{
	// 아래 처럼 만들면 결국 "init" 은 3회 호출됩니다.
	// => 한번만 호출되게 할수 없을까요 ?
	// => "std::call_once 기술"=> 다음 소스에서 
    std::thread t1(foo);
	std::thread t2(foo);
	std::thread t3(foo);
    t1.join();
	t2.join();
	t3.join();
}



