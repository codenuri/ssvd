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
	std::packaged_task<int(int, int)> task1(add);
	std::packaged_task<int()>         task2(std::bind(add, 1, 2));

	// task1 사용시 : 인자 2개 전달
	// task2 사용시 : 인자 없음
	task1(1, 2);
	task2();    // add(1,2)
}  