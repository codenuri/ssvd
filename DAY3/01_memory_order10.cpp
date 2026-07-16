#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

class Singleton
{
private:
    Singleton() = default;
    static std::atomic<Singleton*> sinstance;
	static std::mutex mtx;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
	
	// 최적화 해 봅시다.
	// 1. atomic 변수로만 계속 작업하면
	//    => 매번 load(), store() 해야 합니다.(동기적 읽기/쓰기)
	//    => 지역변수에 옮겨서 사용하면 필요할때만 다시 load/store 하면 됩니다.

	// 2. 이제 지역변수로 작업을 하는데
	// => 다시 load/store 가 필요한 부분에서 직접 load
	// => std::memory_order 를 적절하게 사용

	// 구글에서 "C++ DCLP" 검색후 "preshing.com" 자료 확인
	// => 아래 구현을 처음으로 소개한 사이트
	// => 많은 개발자가 참고한 C++ 업계의 유명한 자료
    static Singleton* getInstance()
    {
		Singleton* temp = sinstance.load( std::memory_order_acquire ); 
		
		if ( temp == nullptr )	 
		{
			std::lock_guard<std::mutex> g(m);
			temp = sinstance.load(std::memory_order_relaxed ); 

			if ( temp == nullptr ) 
			{
				temp = new Singleton;
				sinstance.store(temp, std::memory_order_release );
			}
		}
//		return sinstance; // sinstance.load(std::memory_order_seq_cst); 의미
		return temp;  // 이렇게 하면 위처럼 다시 load 할 필요 없습니다.
    }
};

std::atomic<Singleton*> Singleton::sinstance = nullptr;
std::mutex Singleton::mtx;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}