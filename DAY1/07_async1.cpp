#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 스레드를 고려하지 않고 만든 일반 함수를 스레드로 수행하고 결과를 얻는 방법
// 방법 #1. std::packaged_task
// 방법 #2. std::async

int add(int a, int b)
{
	std::this_thread::sleep_for(1s);
	return a + b;	
}

int main()
{
	// std::async(함수, 인자...) : 함수를 비동기로 실행하고 결과를 담은 future 를 반환
	// 비동기 실행 : 호출시 즉시 반환하고 함수 실행은 별도로
	//              => 결국 내부적으로 스레드 생성해서 실행
	// 
	std::future<int> ft = std::async(add, 10, 20); // 내부적으로 스레드를 만들어서
													// add(10,20) 수행하고
													// 미래 결과를 담은 future 반환
	// 이제 다른 작업을 하다고 결과가 필요하면 ft.get()으로 획득
	// => 결과가 없으면 대기
	int ret = ft.get();	

	std::cout << "result: " << ret << std::endl;
}


