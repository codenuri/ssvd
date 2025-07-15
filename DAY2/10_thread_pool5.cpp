#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>
#include <functional>
using namespace std::literals;

int add(int a, int b)
{
	return a + b;
}

int main()
{
	// packaged_task 객체 사용하기

	std::packaged_task<int(int, int)> task1(&add);		// task1 사용시 인자 2개 전달 해야 합니다.

	std::packaged_task<int()> task2(std::bind(&add, 1, 2)); // task2 는 "add 와 1, 2" 를 모두 보관
															// task2 는 인자 없이 호출

	std::future<int> ft = task2.get_future(); // A. 결과 미리 얻기

	task1(1, 2);

	task2();

	//------------ 
	// 이제 pool 에 함수 포인터가 아닌
	// 함수포인터를 담고 있는 packaged_task 를 넣으면 됩니다. (반환값 꺼내 줄수 있습니다.)

	// 함수 포인터 : 함수주소만 보관, 람다등은 안됨
	
	// std::function<void()> : 호출 가능한 모든 것을 보관 가능(함수, 람다등)
	//						   단, 복사가 가능한 타입 이어야 한다.

//	void(*f2)() = task2; // error

//	std::function<void()> f2 = task2; // error
										// packaged_task 는 복사 불가능.

	// 최종 해결책
	// => packaged_task 를 실행하는 람다표현식을 std::function<void()> 에 보관가능
	using TASK = std::function<void()>;

	std::queue<TASK> Q;
	Q.push([&task2](){ task2();});

	auto f3 = Q.front();
	f3(); // add(1,2); 

	// 의미
	// => 결국 Q에 보관했다가 나중에 호출하지만, 결과를 위 "A" 부분에서 미리 꺼낼수 있게 되엇습니다.
	
}