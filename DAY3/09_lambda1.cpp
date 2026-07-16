// 09_lambda1.cpp

#include <iostream>
#include <algorithm>
#include <functional>

// 람다 표현식을 정확히 이해하려면
// 1. 함수 객체를 먼저 알아야 합니다
// 2. 람다표현식은 함수 객체를 자동으로 만드는 표기법

struct Plus
{
	int operator()(int a, int b) 
	{
		return a + b;
	}
};

int main()
{
	Plus p;

	int n1 = p(1,2); // 핵심
	int n2 = p.operator()(1,2); // 원리
}