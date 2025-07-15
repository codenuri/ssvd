#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;
std::atomic<int> flag = 0;

// release - acquire 모델
// => release 이전의 모든 코드는 
// => acquire 이후에 읽을수 있어야 한다.
// 1. release 위의 코드가 release 아래로 내려가는 것을 막고(reordering)
// 2. release 이전 코드의 값은 acquire 이후에는 메모리에 있음을 보장해야 한다.

// 아래 코드는 A, B 의 순서는 변경될수 있지만
// goo() 에서 acquire 이후에는 data1, data2 를 모두 읽을수 있다는 보장이 있습니다.
void foo()
{
    data1.store(100, std::memory_order_relaxed); // A
    data2.store(200, std::memory_order_relaxed); // B

    flag.store(1, std::memory_order_release );  // <===
}

void goo()
{
    if ( flag.load( std::memory_order_acquire) > 0)
    {
        assert(data1.load(std::memory_order_relaxed) == 100);
        assert(data2.load(std::memory_order_relaxed) == 200);
    }
}

int main()
{
    std::thread t1(foo);
    std::thread t2(goo);
    t1.join(); t2.join();
}