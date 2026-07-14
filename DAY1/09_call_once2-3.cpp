#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static Singleton* sinstance;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

	// static 멤버 데이터 : 클래스 외부 선언 필요
	// inline static 멤버 데이터 : 클래스 외부 선언 필요 없음. C++17 문법 
	inline static std::mutex mtx;

	// case #2. std::mutex 도입하는 경우
	// => 
    static Singleton* getInstance()
    {
		mtx.lock();

		if ( sinstance == nullptr )
		{
        	sinstance = new Singleton;
		}

		mtx.unlock();
        return sinstance;
    }
};
Singleton* Singleton::sinstance = nullptr;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}



