#include <iostream>
#include <atomic>
#include <thread>

/*
template<typename T>
class atomic 
{
	T value;

	// 모든 구현은 value 가 다양한 타입임을 고려해서 설계 되어야 합니다.
	// 제약이 있을수 밖에 없습니다.
};


class atomic_flag 
{
	// value 가 bool 이라는 확정이 있으므로
	// 보다 최적화된 설계가 가능합니다.
	// 모든 C++ 표준 구현은 관련 연산을 lock-free 로 제공해야 합니다.
};
*/



class spinlock
{
	std::atomic_flag flag = ATOMIC_FLAG_INIT; // C++20 부터는 초기화 없어도 됨. 
public:
	void lock() { while (flag.test_and_set()); }
	void unlock() { flag.clear(); }
};
spinlock spin;

void work()
{
	spin.lock();
	std::cout << "start. using shared resource" << std::endl;
	std::cout << "end.   using shared resource" << std::endl;
	spin.unlock();
}

int main()
{
	std::thread t1(work),t2(work);

	t1.join();
	t2.join();
}
