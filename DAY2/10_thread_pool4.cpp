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
	int ret1 = add(1,2);
}