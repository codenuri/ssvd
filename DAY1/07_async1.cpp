#include <iostream>
#include <thread>
#include <future>

// 위와 같은 스레드를 고려하지 않은 일반 함수를 
// 스레드로 수행하고 결과를 얻는 방법
// 방법 #1. std::packaged_task
// 방법 #2. std::async

int add(int a, int b)
{
	return a + b;	
}

int main()
{
	// std::async(함수, 인자...) : 함수를 비동기로 실행하고 결과를 담은 future 를 반환

	std::future<int> ft = std::async(add, 10, 20);


	int ret = ft.get();

	std::cout << "result: " << ret << std::endl;
}


