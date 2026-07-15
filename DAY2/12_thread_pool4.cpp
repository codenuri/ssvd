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
}  
