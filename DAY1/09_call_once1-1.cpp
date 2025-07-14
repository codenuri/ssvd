#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;


// 핵심 : call once 기술 사용방법

// #1. std::once_flag 전역변수 생성
std::once_flag flag;

void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

void foo()
{
    std::cout << "start foo" << std::endl;

	// #2. init 호출시 std::call_once 사용
//    init(10, 3.4); 
	std::call_once(flag, init, 10, 3.4); // init(10, 3.4)를 한번만 호출해 달라. 

	// 특징 
	// 1. 첫번째 스레드가 실행시 init(10, 3.4) 수행
	// 2. 이후 스레드는 (1)의 수행이 종료되지 않았으면 대기. 즉, 현재 코드에서 2초 대기
	// 3. 즉, init() 은 한번만 실행되고
	//    모든 스레드의 call_once 이후 코드는 최초 init() 실행종료되어야 실행 됨.!



    std::cout << "finish foo" << std::endl;
}
int main()
{

    std::thread t1(foo);
	std::thread t2(foo);
	std::thread t3(foo);
    t1.join();
	t2.join();
	t3.join();
}



