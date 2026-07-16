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

	// DCLP : if 문을 2번 만들자는 의도
	// 최초 호출 : if 문을 2번 실행, 한번이면 되는데, 2번실행하게 되므로 약간의 오버헤드
	// 나머지호출 : lock()/unlock() 없이 if 로만 조사하므로 빠르다.

	// 문제점 : sinstance 가 공유 자원인데, A 부분에서 동기화 없이 사용
	//		   B 는 mutex.lock() 후 사용이므로 문제 없음
    static Singleton* getInstance()
    {
		if ( sinstance == nullptr )	 // A
		{
			std::lock_guard<std::mutex> g(m);

			if ( sinstance == nullptr )  // B
			{
				sinstance = new Singleton;
			}
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