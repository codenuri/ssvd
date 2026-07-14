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

	// std::call_once 기술이 아닌 NULL check 기술
	// => 유명한 기술
	// case #1. 아래 코드는 싱글 스레드는 오직 한개의 객체를 보장할수 있습니다.
	//          하지만 멀티 스레드 환경에서는 오직 한개임이 보장 안됩니다.
    static Singleton* getInstance()
    {
		if ( sinstance == nullptr )
		{
        	sinstance = new Singleton;
		}
        return sinstance;
    }
};
Singleton* Singleton::sinstance = nullptr;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}



