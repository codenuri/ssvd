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

// std::memory_order_acq_rel 
// => release & acquire 를 동시에



int c = 0;
int a = 0;
std::atomic<int> b = 0;

void threadA()
{
	c = 1;

    a = b + 1; 

    b.store(1, std::memory_order_release); // b = 1

}

void threadB()
{
	c = 10;

	// release 와 acquire 를 동시에
	// 즉, threadA 의 release 이전값을 읽을수 있고
	// 이순간 나의 위코드c = 10 를 publish
	// => 다른 스레드가 C 를 읽을수 있도록
    if (b.load(std::memory_order_acq_rel) == 1)
    {	
		assert( a == 1 ); 		
    }
}

int main()
{
}
