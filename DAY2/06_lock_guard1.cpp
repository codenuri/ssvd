#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;

// bad code
// => lock(), unlock() 을 직접 사용하면 좋지 않다 

// [핵심] 자원은 반납을 함수 마지막 부분에서 하는 것은 좋지 않다
// => 함수가 마지막 부분 까지 도착한다는 보장이 없다
// => 함수 중간에 예외가 발생하거나, 
// => 나중에 추가한 코드에서 return 문이 추가될수도 있다.
void goo()
{
    m.lock();    
    std::cout << "using shared data" << std::endl;

	// 함수 중간에서 예외 발생
	// => 이순간 catch 로 이동하는데 unlock 안하고 이동 하므로.. 대기중인 스레드는 deadlock 
	throw std::exception();

	// 나중에 추가한 코드에서 return 문 추가
	/*
	if (...)
	{
		// 실수로 unlock 안함
		return;
	}
	*/
    m.unlock();
}

void foo()
{
    goo();
}

int main()
{
    std::jthread t1(foo);
    std::jthread t2(foo);
}



