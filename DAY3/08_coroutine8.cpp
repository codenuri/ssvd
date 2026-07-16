#include <iostream>
#include <coroutine>
#include <utility>
#include <generator> 

// C++ coroutine 으로 파이썬 range 만들기
std::generator<int> range(int start, int end)
{
	for( int i = start; i < end; ++i ) 
		co_yield i;
}

int main()
{	
	// 파이썬 코드 - 0 ~ 9 를 순회할때 사용
	// range : start, end 값을 연속적으로 생성
	// for e in range(0, 10)
	for( auto e : range(0, 10) )
	{
		std::cout << e << '\n';
	}		
}

// 결론
// 1. coroutine-framework 를 정확히 안다면 "std::generator<>" 등을 직접 구현도 가능하고
//    다양한 기능을 coroutine 으로 만들수 있습니다.

// 2. coroutine-framework 를 몰라도 "std::generator<>" 같은 클래스 사용법만 알아도
//    특정 용도의 coroutine 제작 가능

// coroutine 활용
// 1. 값 생성기 -> std::generator<>

// 2. async/await 기술 -> C#, python 의 비동기 대기 기술
//    co_await 파일 다운로드 비동기요청 => 요청만하고 main 으로 이동.. 완료후 다시 아래로(resume)

// 3. 게임등에서 상호 협력하면서 동시에 여러가지 처리

// 4. .... 