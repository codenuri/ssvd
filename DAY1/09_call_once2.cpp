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

	// 싱글톤 : 오직 한개의 객체만 만들수 있게 하는 디자인 패턴
	// => 아래 처럼 만들면 여러번 호출하면 여러개 객체 생성
	// => 오직 한개만 만들게 해봅시다. - 다음 소스에서
    static Singleton* getInstance()
    {
        sinstance = new Singleton;
        return sinstance;
    }
};
Singleton* Singleton::sinstance = nullptr;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}



