#include <iostream>
#include <thread>
#include "chronometry.h"

constexpr int sz = 10'000;

// 크기가 큰 배열!!
int arr[sz][sz];

void f1()
{
	// 배열의 모든 요소를 차례대로 접근([i][j])
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			arr[i][j] = 0;
		}
	}
}
void f2()
{
	// 핵심 : 요소 접근을 i, j 가 아닌 j, i
	// => 캐쉬 적중률이 좋지 않습니다.
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			arr[j][i] = 0;
		}
	}
}

int main()
{
	chronometry(f1);
	chronometry(f2);
}
