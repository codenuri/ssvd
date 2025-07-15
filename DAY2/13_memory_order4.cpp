#include <thread>
#include <atomic>
#include <cassert>

std::atomic<int> data1 = 0;
std::atomic<int> data2 = 0;
std::atomic<int> flag = 0;

void foo()
{
    data1.store(100, std::memory_order_relaxed);
    data2.store(200, std::memory_order_relaxed);
    flag.store(1, std::memory_order_relaxed); // 이렇게 하면 위 2줄이 이 아래로 내려올수도 있고 reordering
											  // 위 2줄이 실제 캐쉬가 아닌 메모리에 쓰였다는 보장도 없습니다.
											  // 따라서, 아래 goo 코드는 제대로 동작안할수 있습니다.
}

void goo()
{
    if ( flag.load( std::memory_order_relaxed) > 0)
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