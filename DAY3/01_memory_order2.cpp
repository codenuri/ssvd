#include <atomic>
#include <cassert>

// std::memory_order 의 개념
// => 동기화를 어느 단계까지 보장해 줄것인가를 지시하는 상수 값

// std::memory_order_relaxed : 최소 동시접근(data race) 문제만 보장하면 된다.
//							   2개 이상의 스레드 사이에서 R/W 해도 문제 없음 

int a = 0;
std::atomic<int> b = 0;

void threadA()
{
    a = b + 1;  // A
    b.store(1, std::memory_order_relaxed); // b = 1 의 의미 
}

void threadB()
{
    if (b.load(std::memory_order_relaxed) == 1)
    {
		// b에 대한 동시접근만 보장했으므로 재배치는 발생할수 있다
		// b == 1 이라도 a == 1 은 보장할수 없다
		assert( a == 1 ); // 실패 할수도 있다
    }
}

int main()
{
}
