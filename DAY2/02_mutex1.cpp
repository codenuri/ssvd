#include <iostream>
#include <thread>
#include <chrono>
#include <string_view>
#include <mutex>
using namespace std::literals;

void delay() { std::this_thread::sleep_for(20ms); } // 시간 지연 함수


// mutex : 자원의 독점을 위해서 사용
// => 직렬화(serialization)
// => 상호배제(mutual exclusion)

std::mutex m;

void foo(std::string_view name)
{
//   int x = 0;	// 지역변수, stack 에 생성, stack 은 스레드 자원
				// 2개의 스레드가 이 함수를 실행하면, 각각의 stack 에 생성
				// 따라서 실행 결과는 항상 "101"

	static int x = 0; // static 지역변수, static storage 에 생성, 모든 스레드가 공유
					  // 출력결과를 예측할수 없다(100, 101, 102)

    for (int i = 0; i < 10; i++)
    {
		m.lock();	// 한개의 스레드만 lock 을 획득 가능
					// 늦게 도착한 스레드는 소유자가 unlock 할때 까지 대기
		//------------------------------------------
        x = 100;   delay();
        x = x + 1; delay();
        std::cout << name << " : " << x << std::endl; delay();
		//------------------------------------------
		m.unlock();
    }
}

int main()
{
    std::jthread t1(foo, "A");
    std::jthread t2(foo, "\tB");
}



