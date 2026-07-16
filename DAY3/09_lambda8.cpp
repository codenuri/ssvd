#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include "chronometry.h"

constexpr int cnt = 1'000'000;

std::vector<int> v1;
std::vector<int> v2;

void init()
{
	v1.reserve(cnt);
	v2.reserve(cnt);

	for( int i = 0; i < cnt; i++)
	{
		int n = rand();
		v1.push_back(n);
		v2.push_back(n);
	}
}

bool cmp(int a, int b) { return a < b; }

void use_function()
{
	for(int i = 0; i < 10; i++)
	{
		std::sort(v1.begin(), v1.end(), cmp);
	}
}

void use_lambda()
{
	// 핵심 : 비교 정책으로 일반함수가 아닌 람다 표현식 사용 
	for(int i = 0; i < 10; i++)
	{
		std::sort(v2.begin(), v2.end(), [](int a, int b) { return a < b; });
	}
}

int main()
{
	init();

	chronometry(use_function);
	chronometry(use_lambda);
}

// 빠른 이유
// => 인자로 cmp 전달시,    sort() 내부에서 다시 cmp 호출하게 됩니다.
// => 인자로 lambda 전달시, sort() 내부에서 lambda 코드가 인라인 치환됩니다.
// 단, 대부분 컴파일러는 인라인 치환 되려면 최적화 필요한 경우가 많습니다 => -O2 옵션

// g++ 09_lambda8.cpp -std=c++20 -O2     로 컴파일