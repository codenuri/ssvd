#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std::literals;

int add(int a, int b)
{
	return a + b;
}

int main()
{
	// #1. 함수를 (주스레드가) 직접 호출하면 바로 결과를 얻을수 있습니다.
	int ret1 = add(1, 2);

	// #2. 함수를 std::async 로 실행하면, 다른 스레드가 실행 하지만, 미래의 결과를 담은 객체를 얻을수
	//     있습니다.
	// => 함수가 언제 종료될지 모르지만 미래의 결과를 받을수는 있습니다.
	std::future<int> ft = std::async(add, 1, 2);
	int ret2 = ft.get();

	// #3. #2 는 std::async() 호출시 즉시 실행.
	// => 그런데, pool 사용시, Q 에 대기중이다가 실행되게 됩니다.
	// => 실행전에 Q에 대기 시키고 결과를 얻어야 합니다.
	// => std::packaged_task 로하면 됩니다.

	std::packaged_task<int(int, int)> task1(add); // 실행전 이지만
	std::future<int> ft2 = task1.get_future();    // 결과를 꺼낼수 있습니다

//	task2(1, 2);	// 주스레드가실행

	std::thread t1(task2, 1, 2); // 새로운 스레드 실행

	int ret3 = ft2.get();

	t1.join();
}