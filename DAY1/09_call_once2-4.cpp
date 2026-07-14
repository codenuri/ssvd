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
	inline static std::mutex mtx;

	// case #3. DCLP 사용
	// => if 문을 2개 만들자는 패턴
	// => Double Check Locking Pattern 이라는 기술
	// => 1990년 ~ 2000년대 초반에 널리 유행한 기술.. 
	// => 하지만 버그가 발견되어서 C++에서는 사용금지. 

    static Singleton* getInstance()
    {
		if ( sinstance == nullptr )
		{
			mtx.lock();

			if ( sinstance == nullptr )
			{
				sinstance = new Singleton;
			}

			mtx.unlock();
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



