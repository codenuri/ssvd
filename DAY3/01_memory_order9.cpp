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
	
	// 아래 코드는 sinstance 가 std::atomic 이므로 안전한 코드 입니다.
	// 아래 코드는 문제 없습니다.
	// 단, 아래 코드는 std::memory_order 를 명시적으로 지정하지 않으므로
	// 항상 std::memory_order_seq_cst 입니다.
	// => 안전하지만 약간의 오버헤드가 있습니다
	// => 반드시 필요한 제약조건으로 변경하면 빨라 질수 있습니다.

    static Singleton* getInstance()
    {
		//   sinstance.load(std::memory_order_seq_cst) == nullptr 의미
		if ( sinstance == nullptr )	 
		{
			std::lock_guard<std::mutex> g(m);

			if ( sinstance == nullptr ) 
			{
				sinstance = new Singleton;
			}
		}
		return sinstance;
			  // sinstance.load(std::memory_order_seq_cst); 의미
    }
};

std::atomic<Singleton*> Singleton::sinstance = nullptr;
std::mutex Singleton::mtx;

int main()
{
    std::cout << Singleton::getInstance() << std::endl;
    std::cout << Singleton::getInstance() << std::endl;
}