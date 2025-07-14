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

	// 싱글톤 : 오직 한개의 객체만 생성할때 사용하는 디자인 패턴
	
	// 아래처럼 만들면 함수 호출시 마다 객체 생성
    static Singleton* getInstance()
    {
        sinstance = new Singleton;
        return sinstance;
    }

	// 오직 한개의 객체만 만들도록 변경해 봅시다.
};
Singleton* Singleton::sinstance = nullptr;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}



