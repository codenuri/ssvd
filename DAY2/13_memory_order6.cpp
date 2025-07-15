#include <queue>
#include <mutex>
#include <atomic>

std::mutex m;

std::queue<int> Q;

// int x = 0;
// int y = 0;

std::atomic<int> x = 0;
std::atomic<int> y = 0;

// 아래 함수를 여러개 스레드가 실행한다고 생각해 봅시다..
// => 공유자원(전역변수) 는 동기화 되어야 합니다.
void foo()
{
	m.lock();
	Q.push(20); // 이 코드의 동기화는 mutex 로 해야 합니다.
	m.unlock();

	// 아래 코드도 동기화가 필요한데, 단순히 정수 변수에 값을 넣는것을
	// => mutex 로 동기화 하면 오버헤드가 너무 큽니다
	// => lock-free 로 할수 있으므로, int 사용하지 말고, atomic<int> 사용
	// => x, y 를 std::atomic<int> 으로 했다면 아래 코드는 안전. 
	x = 100;
	y = 200;	// 이 코드는 아래 코드와 동일합니다
	y.store(200, std::memory_order_seq_cst); 

	// 위 코드에서 x, y 의 순서 보장이 필요 없다면 아래 처럼 하면
	// 동시접근만 보장, 
	// visibility 와 reordering 은 보장 안함
	x.store(100, std::memory_order_relaxed); 
	y.store(200, std::memory_order_relaxed); 
	
}

int main()
{

}