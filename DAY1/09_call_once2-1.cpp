#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static Singleton* sinstance;

	static std::once_flag flag;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance()
    {
		// 아래 처럼 호출하면 멀티스레드 환경에서도 오직 한번만 호출됨을 보장 합니다.
        std::call_once(flag, initSingleton);
        return sinstance;
    }

	static void initSingleton()
    {
		sinstance = new Singleton;        
    }
};
Singleton* Singleton::sinstance = nullptr;
std::once_flag Singleton::flag;

void foo() 
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}
int main()
{
	std::thread t1(&foo);
	std::thread t2(&foo);

	t1.join();
	t2.join();
}




