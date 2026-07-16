#include <atomic>
#include <cassert>

// 정확히 이해하지 못하고 std::memory_order 사용시
// 버그 원인이 될수 있습니다
// => 이경우 가장 안전한 std::memory_order_seq_cst 사용하세요
// => 모든 atomic 함수에서 std::memory_order 생략시, 디폴트 값이 std::memory_order_seq_cst
//    입니다.

std::atomic<int> c = 0;
std::atomic<int> a = 0;
std::atomic<int> b = 0;

void threadA()
{
	// 아래 3줄은 모두 "std::memory_order_seq_cst" 의미 입니다.
	c.store(1, std::memory_order_seq_cst);
	a.store(1);
    b = 1;

	// 결론 atomic 변수 사용시
	a = 1; 		// 쉬워 보이지만 std::memory_order 변경할 기회 없음
				// 항상 std::memory_order_seq_cst 사용
	a.store(1); // 위와 동일. 2번째 인자로 std::memory_order 변경 가능

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
