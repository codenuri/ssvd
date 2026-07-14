#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std::literals;

// #1. promise 인자의 위치는 자유롭게.
void divide(std::promise<int>& p, int a, int b)
{
	// b 가 0 이면 오류임을 전달해야 합니다.
	// => C++ 에서는 예외를 널리 사용
	// => 그런데, 아래 처럼 하면 안됩니다.
	// => 예외는 같은 스레드에서만 catch 가능합니다. 다른 스레드에서는 catch 안됨
	// if ( b == 0 )
	// 	throw std::runtime_error("divide by zero");

	// 아래 처럼 해야 합니다.
	try 
	{
		// 직접 오류 확인된 경우 
		if ( b == 0 ) 
			throw std::runtime_error("divide by zero");

		// 그외 작업중에도 예외 나올수 있습니다

		// 예외 없이 안전하게 결과가 나왔다면 set_value()로 전달
    	p.set_value(a / b);
	}
	catch(...)	// 모든 종류의 예외 처리
	{
		// 이 부분이 핵심 
		// => 현재 스레드에서 발생한 모든 종류의 예외를
		//    promise 를 통해서 주스레드에 전달
		// std::current_exception() : 현재 발생된 예외 반환
		p.set_exception( std::current_exception() );
	}
}

int main()
{
    std::promise<int> pm;
    std::future<int>  ft = pm.get_future();

    std::thread t(divide, std::ref(pm), 10, 2);

	try 
	{
    	int ret = ft.get();
	}
	catch(std::exception& e)
	{
		std::cout << "스레드 수행중 예외 발생: " << e.what() << std::endl;
	}

    t.join();
}



