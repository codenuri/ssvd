#include <iostream>
#include <thread>
#include <mutex>
#include "chronometry.h"

constexpr unsigned int cnt = 1'000'000;


long x = 0; // 전역변수, 모든 스레드가 공유.

void foo()
{
    for (int i = 0; i < cnt; ++i)
    {
        x = x + 1;  

		// 위 3줄은 아래 3줄의 기계어 코드를 생성합니다.
		// mov a, b : a = b 의미 
		
		// mov eax, x	// eax 레지스터 = x 변수
		// add eax, 1	// eax += 1
		// mov x, eax 	// x 변수 = eax 레지스터

		// 3개의 스레드가 위 코드를 동시에 실행하고, x 는 공유 되므로
		// => 안전하게 1증가하는 것을 보장할수 없습니다.

		// => 해결책은 다음 소스
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
	// "x = x + 1" 이 안전하게 실행되었다면 아래 결과는 3'000'000 이어야 합니다.
    std::cout << x << std::endl;
}
