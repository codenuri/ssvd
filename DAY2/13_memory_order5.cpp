#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;

// std::memory_order_seq_cst
// => 모든 보장을 해달라.
// => 동시접근을 막고, 순서를 변경하지말고, visibility 도 보장해달라.

int main()
{
    data1.store(100, std::memory_order_seq_cst);
    data2.store(200, std::memory_order_seq_cst);
    data2.store(300); // 위와 동일
	data2 = 300;	  // 위와 동일
}
// 결론 atomic<int> data;
// data = 100;
// 은 동기화 3가지 문제를 모두 해결합니다.
// => 그럼, 왜?? std::memory_order_relaxed 를 사용하나요 ??
// => std::memory_order_seq_cst 보다 "std::memory_order_relaxed" 의 기계어가
//    보다 효율적입니다.

// => 다양한 오픈소스는 "memory_order" 를 가장 효율적으로 사용하고 있습니다.
