#include <iostream>
#include <thread>
#include <future>

// std::packaged_task : 함수를 담은 객체를 먼저 생성하고(이전 소스의 task 객체)
//						"std::thread" 객체를 사용해서 "task" 실행

// std::async() : 해당 함수를 즉시 스레드로 실행
//				  사용자가 "std::thread 클래스" 를 사용할 필요 없습니다.
//				 가장 사용하기 쉬운 모델이고, 
//               간단한 스레드 작업에는 가장 권장되는 모델

int add(int a, int b)
{
	return a + b;
}

int main()
{
	// #1. add(10,20) 를 스레드로 실행해 달라. 
	std::future<int> ft = std::async(add, 10, 20);

	// #2. future 객체로 결과를 얻어서 사용
	int ret = ft.get();

	std::cout << "결과 : " << ret << std::endl;
}

// 스레드 풀
// => 수백개의 작업을 할때 수백개의 스레드를 만들지 말고
// => 일정 갯수만 만든후에
// => 해야 하는 작업은 "큐"에 보관했다가 차례대로 수행
// => 이런 고급 작업은 "작업 자체"를 즉시 실행이 아닌 "큐 보관"
// => std::packaged_task 같은 도구 사용


