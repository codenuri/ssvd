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
	result = a + b;	// 복잡한 연산!!

	// 연산이 완료 되었다 - A

	// 이 함수가 사용한 다양한 자원을 정리하고 종료 - B
}

int main()
{
	int result = 0;
	std::thread t(add, 10, 20, std::ref(result));

	t.join(); // 이 코드는 연산의 종료를 대기하는 것이 아니라(A 부분을 대기하는 것이 아니고)
			  // 스레드 종료를 대기 하는 것.. 
			  // 즉, 이미 연산이 종료되어도, 즉시 결과를 얻을수는 없다 

	std::cout << result << std::endl;
}



