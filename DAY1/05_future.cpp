#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void add(std::promise<int>&& p, int a, int b)
{
    std::this_thread::sleep_for(1s);
    p.set_value(a + b);
}

int main()
{
    std::promise<int> pm;
    std::future<int> ft = pm.get_future();

    std::thread t(add, std::move(pm), 10, 20);

	// #1. 아래 처럼 작성하면
	// => promise.set_value() 할때 까지 무한 대기 합니다.
    // int n1 = ft.get(); 

	// #2. 아래 처럼 대기 가능합니다.
	std::future_status ret = ft.wait_for(2s); // 2초간 대기

	if ( ret == std::future_status::ready )
	{
		// promise 통해서 값이 들어온 경우 - ft.get()이 항상 안전하다.
		int ret = ft.get();
	}
	else if ( ret == std::future_status::timeout )
	{
		// 2초가 지난 경우
		std::cout << "time out\n";
	}
	else  // ret == std::future_status::deffered 
	{
		// 스레드가 아직 실행되지 않은 경우
		// => 현재 코드에서는 이 경우는 발생하지 않습니다.
		// => std::async 의 경우에 이 반환값이 나올수 있습니다.
	}


    t.join();
}



