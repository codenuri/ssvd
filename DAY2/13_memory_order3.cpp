#include <thread>
#include <atomic>

// atomic 을 사용하면 동기화 문제를 해결 가능
// => 인자로 전달하는 값에 따라서 "동기화의 종류가 결정"
std::atomic<int> x = 0;
std::atomic<int> y = 0;

// std::memory_order_relaxed
// => 접근 동기화만 보장해 달라.(동시 접근 금지)
// => reordering 문제는 보장되지 않습니다. (아래 코드에서 A, B는 순서가 변경될수도 있습니다.)
// => visibility 도 보장 할수 없습니다

// => 가장 빠르게 동작할수 있고, 가벼운 옵션

void foo()
{
    int n1 = y.load(std::memory_order_relaxed); // A
    x.store(n1, std::memory_order_relaxed);		// B
}

void goo()
{
    int n2 = x.load(std::memory_order_relaxed);
    y.store(100, std::memory_order_relaxed);
}

int main()
{
    std::thread t1(foo);
    std::thread t2(goo);
    t1.join(); t2.join();
}