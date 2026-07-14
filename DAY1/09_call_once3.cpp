#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton()
    {
        std::cout << "start ctor" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish ctor" << std::endl;
    }
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

	// singleton1, 2번 : 오직 한개의 객체를 힙에 만드는 모델
	// singleton3번    : 오직 한개의 객체를 static 지역변수로 만드는 모델

    static Singleton& getInstance()
    {
		// 이 부분은 3개의 스레드가 실행하게 됩니다(A, B, C)
        std::cout << "start getInstance" << std::endl;

		// A 가 먼저 도착 : 최초 도착이므로 생성자 호출 - 10 초 걸림
		// 바로 B, C 가 도착 - 어떻게 될까요 ?
		// => A의 생성자 호출이 종료될때 까지 여기서 대기합니다
		// => 즉, 자동으로 동기화 됩니다.
		// => 이 코드는 멀티 스레드에 안전합니다.
        static Singleton instance;

        std::cout << "finish getInstance" << std::endl;

        return instance;
    }
};
void foo()
{
    Singleton& s = Singleton::getInstance();
    std::cout << &s << std::endl;
}
int main()
{
    std::thread t1(foo);
    std::thread t2(foo);
    std::thread t3(foo);
    t1.join();
    t2.join();
    t3.join();
}


// 멀티 스레드 안전한 싱글톤을 만들고 싶다.
// 1. 위 처럼 static 지역변수로 만드는 singleton 
// => mayer's singleton 이라고 합니다. effective-C++ 저자인 scott-mayer 가 처음 제안한 모델

// 2. std::call_once 기술 사용

// 3. DCLP 을 사용하고 싶다면 - std::memory_order 기술로 reordering 을 막아야 합니다(3일차)

