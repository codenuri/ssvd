#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
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

	// 아래 코드는 "static 지역변수"로 만든 싱글톤 입니다.
	// => 오직 한개의 객체를 static 지역변수로 만드는 모델.

	// 아래 함수를 여러개 스레드가 수행할때 "A" 부분에 대해서 생각해 보세요
	// => A 부분의 코드는 "안전" 합니다.
	// => 최초 스레드가 생성자 호출하고 "3초" 걸리면
	// => 이후 도착하는 모든 스레드는 "생성자 호출이 종료될때 까지" 대기 하게 됩니다.
	//    (call once 와 동일한 효과)
    static Singleton& getInstance()
    {
        std::cout << "start getInstance" << std::endl;

        static Singleton instance; // "A"
        
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



