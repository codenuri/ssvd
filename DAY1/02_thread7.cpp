#include <thread>

// copy, move

void foo() {}
void goo() {}

int main()
{
    std::thread t1(&foo);
    std::thread t2(&goo);

    t2.join();
    t4.join();
}

void f1(std::thread t) 
{
    t.join(); 
}

std::thread f2()
{
    return std::thread(foo());
}
