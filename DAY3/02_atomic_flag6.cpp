#include <iostream>
#include <string_view>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

// 보통은 아래 처럼 클래스로 만들어 사용합니다
class spinlock
{
	std::atomic_flag use_flag = ATOMIC_FLAG_INIT; 
public:
	void lock()   { while(use_flag.test_and_set()); }
	void unlock() { use_flag.clear(); } 
};

std::mutex m;
spinlock   s;	

void work(std::string_view name)
{	
	// 이제 s 는 mutex 처럼 사용하면 됩니다.
	// std::lock_guard<spinlock> g(s) 도 가능
	s.lock();
	std::cout << "using shared resource " << name << std::endl;
	s.unlock();
}




int main()
{
	std::jthread t1(work, "A");
	std::jthread t2(work, "B");
	std::jthread t3(work, "C");

}