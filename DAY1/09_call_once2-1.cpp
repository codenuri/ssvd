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

	// call_once 기술 사용
	// => 아래 처럼 만들면, 단일/다중 스레드 환경에서 모두 initSingleton() 가 한번만 호출됨을 보장합니다
	static std::once_flag flag;

    static Singleton* getInstance()
    {
//      initSingleton();

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
	// 2개의 스레드가 2번의 getInstance() 호출
	// => 총 4번의 호출이지만
	// => initSingleton() 는 한번만 호출됨을 보장
	// => 멀티스레드 환경에서도 안전한 싱글톤 코드 완성
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;	
}

int main()
{
	
	std::jthread t1(foo);
	std::jthread t2(foo);

}



