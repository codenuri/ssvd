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

	std::packaged_task<int(int, int)> task1(&add);

	std::packaged_task<int()> task2(std::bind(&add, 1, 2));

	task1(1, 2);

	task2();

	
}