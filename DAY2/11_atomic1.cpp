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

		// 위 한줄은 기계어(어셈블리)로 아래와 같습니다.
		// mov eax, x
		// add eax, 1
		// mov x, eax 

		// 결국 위 코드를 한개이상의 스레드가 수행하면 "안전하게 1증가" 한다는 보장 없습니다
		// => 동기화 해야 합니다.
		// => 해결 방법은 다음 소스
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
    std::cout << x << std::endl;
}
