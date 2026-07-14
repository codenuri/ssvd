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
	// => 멀티 스레드 환경에서도 오직 한개만 생성됨을 보장
	// 하지만 성능을 생각해 봅시다.
	// getInstance()를 100번 호출시
	// => 최초 호출   : 객체 생성
	// => 나머지 99번 : 생성된 객체를 반환만 합니다.
	//				   반환만 하면 되는데, mtx.lock(), mtx.unlock()을 거쳐야 합니다.
	//				   성능이 좋지 않습니다.
	//				   해결책 : DCLP ????
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



