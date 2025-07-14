#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

void foo(std::promise<int>&& p)
{
    std::cout << "start foo" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "finish foo" << std::endl;
    p.set_value(10);
}
int main()
{
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(foo, std::move(p));
    t.detach();

	// std::async 가 반환한 future : 소멸자에서 get() 수행
	// std::promise, std::packaged_task가 반환한 future : 소멸자에서 get()안함.

//  ft.get();
}



