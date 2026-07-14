#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 일반적인 단일 스레드 프로그래밍 에서는
// => 함수 결과는 return 값으로 전달합니다
// => 멀티 스레드 환경에서는 함수 반환값을 받을수 없습니다.
/*
int add(int a, int b)
{
	return a + b;
}
*/
// 멀티스레드 환경에서 다른 스레드가 수행한 함수의 결과를 얻는 방법
// 방법 #1. out parameter 사용

void add(int a, int b, int& result)
{
	result = a + b;
}

int main()
{
	int result = 0;
	std::jthread t(add, 10, 20, std::ref(result));

	std::cout << result << std::endl;

}



