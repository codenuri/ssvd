#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std::literals;

int add(int a, int b)
{
	return a + b;
}

int main()
{	
	// 함수의 반환값을 얻는 방법

	// #1. 직접 호출하면 "함수 종료후" 에 결과를 얻을수 있습니다.
	int ret1 = add(1, 2);

	// #2. std::async() 를 사용하면, 다른 스레드로 실행되지만, 
	//     "함수 종료 전" 에도 미래의 결과를 얻을수 있습니다.
	//     의미 : 종료전에도 결과를 담는 변수를 만들수 있다는 점..
	std::future<int> ft1 = std::async(add, 1, 2);

	
	// #3. std::packaged_task 를 사용하면 "함수 호출 전" 에도 결과를 담는 변수 생성이 가능합니다.
	std::packaged_task<int(int, int)> task(add);
	std::future<int> ft2 = task.get_future(); // add 를 호출(실행)한적도 없음..

	std::thread t(std::ref(task), 1, 2);

	int ret2 = ft2.get();

	t.join();
}  
