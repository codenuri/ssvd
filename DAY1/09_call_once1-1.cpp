// call_once1-1.cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;


void init(int a, double d)
{
    std::cout << "init" << std::endl;
    std::this_thread::sleep_for(2s);
}

// std::call_once 기술을 사용하는 방법

// #1. std::once_flag 타입의 전역변수 생성
std::once_flag flag;

void foo()
{
    std::cout << "start foo" << std::endl;

	// #2. 여러개 스레드가 수행되더라도 한번만 호출되게 하고 싶은 함수를 호출할때는
	// => std::call_once()를 사용
	//init(10, 3.4);     

	std::call_once(flag, init, 10, 3.4); // init(10, 3.4) 를 오직 한번만 호출됨을 보장


    std::cout << "finish foo" << std::endl;
}
int main()
{
    std::jthread t1(foo);
	std::jthread t2(foo);
	std::jthread t3(foo);
    
}



