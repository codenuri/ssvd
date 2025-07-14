#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

void divide(std::promise<int>& p, int a, int b)
{
	// 아래 처럼만 만들면 주스레드에 전달 안됩니다.
//	if ( b == 0 )
//		throw std::runtime_exception("divide by zero");

	// 아래 처럼 해야 합니다.
	try 
	{
		if ( b == 0 )
			throw std::runtime_exception("divide by zero");	

		// 이제 이 안에서 예외 가능성이 있는 모든 코드를 작성합니다.
		p.set_value(a / b);
	}
	catch(...)	// 발생한 모든 스레드를 일단 받아서
	{
		// 이제 promise 를 통해서 주스레드에 그대로 전달합니다.
		// => future 의 get() 함수로 전달
		p.set_exception( std::current_exception() );		
	} 	
}

int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

//  std::thread t(divide, std::ref(pm), 10, 2);
	std::thread t(divide, std::ref(pm), 10, 0); // 0 으로 나누는 것은 예외가 발생합니다.

	try 
	{
    	int ret = ft.get();	// 이순간 promise 의 set_exception() 으로 발생한 예외가 전달
	}
	catch(...)
	{
		std::cout << "예외 발생\n";
	}

    t.join();
}



