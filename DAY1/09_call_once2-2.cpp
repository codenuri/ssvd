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



