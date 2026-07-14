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

	std::cout << "finish add: " << std::this_thread::get_id() << std::endl;
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
	
	std::cout << "continue main: " << std::this_thread::get_id() << std::endl;

	// 이제 다른 작업을 하다고 결과가 필요하면 ft.get()으로 획득
	// => 결과가 없으면 대기
	int ret = ft.get();	

	std::cout << "result: " << ret << std::endl;
}

// promise/future
// => "return 값" 의 결과를 얻는 것이 아니라
// => promise.set_value(값)의 결과를 future로 꺼내는 것
// => 즉, 함수 자체를 스레드 전용으로 설계

// 일반 함수 처럼 "return 값" 으로 된 함수를 다른 스레드로 실행해서 결과 얻으려면

// 1. std::async() 사용
// => 즉시 스레드를 생성해서 해당 함수 호출하고 결과를 future 로 얻기 

// 2. std::pakaged_task 사용
// => 바로 호출이 아니라 task 형태의 객체로 만들어서, 나중에 필요할때 호출
// => 내일 예제에서 "수십개의 task 를 vector(Q같은 개념) 에 보관했다가" N 개의 스레드로 나누어 실행
//    할일이 100이상인데, 100개의 스레드 생성은 오버헤드가 크다.

//----------------------------------------
// C++ 에서 스레드를 생성할수 있는 2가지 방법

// #1. std::thread, std::jthread 클래스 사용
// => 가장 기본적인 방법
// => 스레드를 직접 제어하고 싶을때 

// 2. std::async()
// => 내부적으로 다시 "std::thread" 등을 사용해서 스레드를 생성하고
// => 함수의 "return 결과" 에서 "결과" 를 future 로 반환할수 있도록 만든것 

// 업무상 간단하게 함수를 스레드 수행하고 결과만 얻고 싶다.
// => std::async() 를 먼저 권장.

// 다양한 스레드 기술을 사용하고 스레드간 통신등도 해야 한다
// => std::thread, std::jthread 를 직접 사용