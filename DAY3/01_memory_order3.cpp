#include <atomic>
#include <cassert>

// std::memory_order 의 개념
// => 동기화를 어느 단계까지 보장해 줄것인가를 지시하는 상수 값

// std::memory_order_relaxed 
// => 최소 동시접근(data race) 문제만 보장하면 된다.
// => 2개 이상의 스레드 사이에서 R/W 해도 문제 없음 

// std::memory_order_release
// std::memory_order_acquire
// => 동시접근(data race) 보장 + 가시성 보장
// => release 이전 코드를 acquire 이후에서 확인 가능
// => std::memory_order_relaxed 보다는 오버헤드가 있을수 있다 




int c = 0;
int a = 0;
std::atomic<int> b = 0;

void threadA()
{
	c = 1;

    a = b + 1;  // A

    b.store(1, std::memory_order_release); // b = 1
				// b 를 acquire 로 읽는 스레드에서는 
				// release 이전의 변경된 메모리 상태를 읽을수 있어야 한다.
				// 즉, 이 줄의 위의 코드는 메모리에 반영되어야 한다.
				// "공개(publish)" 한다고 표현
}

void threadB()
{
    if (b.load(std::memory_order_acquire) == 1)
    {
		// b 를 acqure 로 얻은 경우 release 이전 코드를 여기서 보장받을수 있습니다.
		assert( a == 1 ); 
		assert( c == 1 ); 

		// 단, c 와 a의 실행순서는 변경되었을수도 있습니다.
		// 대신, b == 1 이후는 c, a 가 모두 실행은 완료
    }
}

int main()
{
}
