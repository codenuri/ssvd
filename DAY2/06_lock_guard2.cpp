#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// 1-1번에서 만든 lock_guard 는 이미 표준에 있습니다
// => "std::lock_guard"

std::mutex m;

void foo()
{	
	// 함수 끝날때 가 아닌 함수 중간에서 unlock()을 하려면
	// => {} 를 사용하세요
	// => 동기화 구간을 {}으로 "들여쓰기"로 표현하므로 읽기 좋은 코드 이기도 합니다(좋은 코드)
	
	{
		std::lock_guard<std::mutex> lg(m);
		std::cout << "using shared data" << std::endl;

	} // <== m.unlock()

	// ....

}

int main()
{
	std::jthread t1(foo);
	std::jthread t2(foo);
}



