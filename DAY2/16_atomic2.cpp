#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

long x = 0;

std::mutex m;

void foo()
{
    for (int i = 0; i < 1'000'000; ++i)
    {
		// 해결책 #1. std::mutex 사용
		// => 단점 : 단순 1증가를 위해 mutex 를 사용하는 것은 overhead 가 크다. 
		// m.lock();
        // ++x; 
		// m.unlock();

		// 해결책 #2. 멀티 스레드에 안전한 기계어 코드 사용
		// => 코어가 여러개인 CPU 에서 특정 변수를 안전하게 1증가하는 인텔이 제공하는 기계어 코드
		// => 한나의 코어가 x 접근해서 1증가하는 동안 다른 CPU 는 절대 x 접근 금지
		// => "lock" 이라는 기계어 코드가 하는 일
		// lock inc x	
		// => 의미 "안전하게 1증가" 를 위해 "OS의 도구" 가 아닌 "CPU의 기능"을 사용
		// => "lock-free" 라고 불리는 기술
		// => 정말 lock 이 없는 것이 아니라, "OS의 lock이 없이 CPU 기능으로 해결" 
		
		// 기계어 코드를 직접 사용할수 없으므로 이 내용으로 만들어진 C 함수 호출
		fetch_add(&x, 1);

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
