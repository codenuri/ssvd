#include <iostream>
#include <thread>

void foo(int a, int b)
{
    std::cout << "foo : " << a << ", " << b << std::endl;
}

int main()
{
    std::thread t1(&foo, 10, 20);
    std::thread t2(&foo, 10, 20);

    t1.join();
    t2.join();
}

