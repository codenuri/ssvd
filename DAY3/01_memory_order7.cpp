#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static Singleton* sinstance;
	static std::mutex mtx;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

	// 특징
	// 1. mutex 로 동기화 하므로 "thread-safe" 하다
	// 2. 최초 1회 호출 : singleton 객체 생성. lock 필요
	//    나머지 호출   : 단지 포인터만 반환. 
	// 					 그럼에도 lock()/unlock() 이 호출됨
	//					 성능저하

	// 문제점은 없지만, 성능저하가 있습니다.
	// => 해결책이 "Double Checking Locking Pattern"
	// => 다음소스
    static Singleton* getInstance()
    {
		std::lock_guard<std::mutex> g(m);

		if ( sinstance == nullptr )
		{
			sinstance = new Singleton;
		}

		return sinstance;
    }
};
Singleton* Singleton::sinstance = nullptr;
std::mutex Singleton::mtx;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}