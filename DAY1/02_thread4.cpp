#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

// 스레드 ID

void foo()
{
    std::cout << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(1s);
}
int main()
{
    std::thread t(&foo);
    
	// 이번 소스 핵심
	std::thread::id tid1 = std::this_thread::get_id(); // 현재 스레드(주스레드, main 함수실행) ID
    std::thread::id tid2 = t.get_id();				   // 새롭게 생성된 스레드의(foo 실행) 스레드 ID
    
    std::cout << "main    thread id : " << tid1 << std::endl;
	std::cout << "created thread id : " << tid2 << std::endl;


    t.join();
}

