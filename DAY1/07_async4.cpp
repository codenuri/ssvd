#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

void foo(std::promise<int>& p)
{
    std::cout << "start foo" << std::endl;
    std::this_thread::sleep_for(3s);
    std::cout << "finish foo" << std::endl;
    p.set_value(10);
}
// std::async()
// => 내부적으로 직접 스레드 생성
// => 스레드 강제 종료를 막기 위해 future 의 소멸자에서 get()으로 대기하는 코드 있음.

// std::promise
// => 사용자가 직접 스레드를 만들게됨.
// => 따라서 스레드 대기도 사용자 책임
// => 따라서 promise가 반환하는 future의 소멸자는 대기 안함
int main()
{
    std::promise<int> p;
    std::future<int> ft = p.get_future();

    std::thread t(foo, std::ref(p));
    t.detach();

//    ft.get();
}	// ft 가 async() 의 반환 값이라면 소멸자에서 get()호출해서 대기
	//       promise 의 반환 값이라면 소멸자에서 대기 안함
	//			=> promise 는 사용자가 스레드를 생성하므로 대기도 사용자 책임



