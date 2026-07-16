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


// std::memory_order_seq_cst
// => 동시 접근(relaxed) + 가시성(release, acquire) 
// => 에 추가로 "순차실행(재배치 금지)" 까지 보장
// => 모든 문제를 보장해 달라.
// => 오버헤드가 큽니다

// [의미]
// => 어떤 "std::memory_order" 를 사용하는가에 따라 기계어 코드가 보다 효율적으로 달라질수 있습니다

// 위 분류는 "C++ 언어가 만든 추상적인 개념"
// => CPU 마다 결과가 다를 수 있습니다
// => 단순한 명령만 가진 CPU 는 "relaxed" 와 "seq_cst" 의 기계어가 완전 동일할수도 있습니다.

std::atomic<int> c = 0;
std::atomic<int> a = 0;
std::atomic<int> b = 0;

void threadA()
{
	c.store(1, std::memory_order_seq_cst);
	a.store(1, std::memory_order_seq_cst);
    b.store(1, std::memory_order_seq_cst); // b = 1

}

void threadB()
{
	c = 10;

	if (b.load(std::memory_order_seq_cst) == 1)
    {	
		// A 스레드에서 실행된 순서까지 보장됨
		// c, a, b 순으로 실행이 완료 되었다고 보장
		assert( a == 1 ); 	

    }
}

int main()
{
}
