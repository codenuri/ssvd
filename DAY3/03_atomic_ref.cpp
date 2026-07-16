#include <iostream>
#include <thread>
#include <atomic>

// 아래 구조체는 멀티스레드를 고려하지 않고 설계된 구조체
struct Machine
{
	// 아래 데이터가 atomic<> 이 아니므로 "thread-safe" 하지 않습니다.
	int data{ 0 };
	int count{ 0 }; 
};
Machine m;	// 전역이므로 멤버 데이터는 모든 스레드에 의해 공유 됩니다.

void foo()
{
	for (int i = 0; i < 1'000'000; i++)
	{
		// 아래 코드는 "thread-safe" 하지 않습니다.
		// ++m.count;

		// thread-safe 하려면
		// 방법 #1. count 변수를 atomic 으로 변경
		// 방법 #2. C++20 에서 추가된 std::atomic_ref 사용
		std::atomic_ref<int> r(m.count);
		// int& r = m.count  의미 인데.. 스레드 안전 기능일 추가된 reference

		// m.count 를 통해 접근시 스레드 안전 아님
		// r 를 통해 접근시 스레드 안전 아님
		++r;
	}
}
int main()
{
	std::thread t1(foo), t2(foo), t3(foo);

	t1.join();
	t2.join();
	t3.join();

	std::cout << m.count << std::endl;
}
