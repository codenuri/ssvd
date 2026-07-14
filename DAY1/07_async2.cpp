#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

int add(int a, int b)
{
    std::cout << "add : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
    return a + b;
}
int main()
{
	// std::async() : "새로운 스레드로 실행해라" 가 아닌 "비동기로 실행해라"
	// std::launch::async 옵션    : 새로운 스레드로 실행하라
	// std::launch::deferred 옵션 : 지연된 실행, ft.get() 할때 실행해달라(스레드 생성안됨)
//  std::future<int> ft = std::async( std::launch::async, add, 10, 20);
//  std::future<int> ft = std::async( std::launch::deferred, add, 10, 20);

	// std::launch::async | std::launch::deferred  의미
	// => 멀티스레드가 지원되는 OS 라면 새로운 스레드 생성해서 실행
	// => 멀티스레드가 지원 안되는 OS 라면 지연된 실행
  	// std::future<int> ft = std::async( std::launch::deferred | std::launch::async, add, 10, 20);

	// 1번째 인자를 생략하면 "위 코드와 동일" 
	std::future<int> ft = std::async(  add, 10, 20);

    std::cout << "continue main : " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);

    int ret = ft.get();

    std::cout << "result : " << ret << std::endl;
}








// async(비동기) 함수 : 호출하면 "즉시 반환 하고" 실행은 다른 다양한 방법으로 ...
//					  => 아래 원리에서 1, 3 번 기술 사용

// 일반적인 비동기 함수 구현 원리(C++뿐 아니라 S/W 세계의 일반적인 이야기)
// 1. 내부적으로 스레드를 생성해서 실행
// 2. OS 에게 실행을 요청 - 주로 H/W 입출력(ex. 파일 읽기)
// 3. 지연된 실행 - 지금 실행하지 말고, 결과가 필요할때 실행해 달라.(멀티스레드 아님.)
// 4. coroutine - 요즘 유행기술
