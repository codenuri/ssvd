#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
using namespace std::literals;

int add(int a, int b)
{
	return a + b;
}
int main()
{	
	// packaged_task 사용하기

	// #1. 인자 고정
	std::packaged_task<int(int, int)> task1(add);
	std::packaged_task<int()>         task2(std::bind(add, 1, 2));

	// 우리가 만든 ThreadPool 내의 스레드는 
	// => 작업 실행시 task() 로 실행

	// task1 사용시 : 인자 2개 전달
	// task2 사용시 : 인자 없음
	task1(1, 2);
	task2();    // add(1,2)
	//-----------
	// #2. 보관
	void(*t)() = task2; // error. 함수 포인터에 packaged_task 보관 못함

	// std::function : 호출 가능한 대부분을 보관 가능. 단 복사 가능 타입만 가능
	std::function<void()> f1 = task2; // error. std::function 에도 packaged_task 보관 못함
									 // std::packaged_task 는 복사 금지 타입
	// 해결책 : std::packaged_task 을 실행하는 람다 표현식을 function 에 등록

	std::function<void()> f1 = [&task2]() { task2(); };

	f1(); // task2();
}  
// 결국
// using TASK = void(*)() 가 아니라 std::function
using TASK = std::function<void()>;

std::queue<TASK> Q;
Q.push([](){ packaged_task 를 실행 });
