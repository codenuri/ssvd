#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// 핵심 : promise 개념 ( 31 page ~ )

// C/C++ 언어의 일반 함수는 결과를 반환 값으로 돌려주게 됩니다.
// => 단일 스레드는 문제 없지만
// => 다른 스레드로 수행되면 주스레드에 결과 전달이 안됩니다.
/*
int add(int a, int b)
{
	int s = a + b;
	return s;
}
*/

// 방법 #1. 결과를 담을 out parameter 사용

void add(int a, int b, int& result )
{
	result = a + b;
}


int main()
{
	int ret = 0;
	std::thread t(add, 10, 20, std::ref(ret));
	t.join();

	std::cout << "결과 : " << ret << std::endl;
}



