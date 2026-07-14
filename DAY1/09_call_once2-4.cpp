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

	// 최초 호출   : 2번의 if 문 수행 - 1번이면 되는데, 2번 하게 되므로 약간의 오버헤드
	// 나머지 호출 : mtx.lock() 대신 if 로 조사후 반환..- case#2 보다 아주 빠르다

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



// 위 기술을 사용하면 안되는 이유
static Singleton* getInstance()
{
	if ( sinstance == nullptr )
	{
		mtx.lock();

		if ( sinstance == nullptr )
		{
			sinstance = new Singleton; // A

			// 위 A 는 컴파일러에 의해 아래 3줄로 변경됩니다.
			// 1. Singleton 크기 메모리 할당      : temp = malloc(sizeof(Singleton));
			// 2. 할당된 메모리(객체)의 생성자 호출 : Singleton::Singleton();
			// 3. 메모리 주소를 sinstance에 대입   : sintance = temp;

		}

		mtx.unlock();
	}
	return sinstance;
}