#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// 반환값

int add(int a, int b)
{
    std::cout << "A. start add" << std::endl; 
    std::this_thread::sleep_for(2s);
    std::cout << "B. finish add" << std::endl; 
    return a + b;
}

int main()
{
	// #1. 아래 코드 실행 결과(화면 로그)를 예측해 보세요
	// => 1. A, C 출력 => 순서는 알수 없음
	// => 2. B
	// => 3. D 
//  std::future<int> ft = std::async( std::launch::async, add, 10, 20);


	// #2. 아래 처럼 std::async 의 반환 값을 받지 않으면 실행결과가 이상해 집니다.
	// => 마치 스레드가 생성되지 않고, 동기적(주스레드가 호출)으로수행되는것 같습니다.
	// => A, B, C, D 순서로 출력
	// => 하지만 스레드가 생성된것이 맞습니다.
	// => 왜 이런 현상이 있는지는 다음 소스에서. 
	std::async( std::launch::async, add, 10, 20);

    std::cout << "C. continue main " << std::endl; 

//  int ret = ft.get();

    std::cout << "D. finish main" << std::endl;	
}



