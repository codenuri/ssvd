#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

// C++ 표준에 앞에서 만든 lock_guard 이미 있습니다.
// => std::lock_guard

std::mutex m;

void foo()
{
	// 함수 끝이 아닌 함수 중간에 unlock 하려면 {} 를 사용하세요
	// => 동기화 부분이  {} 으로 되어 있으므로.. 가독성도 아주 좋은 코드 입니다.
	{
		std::lock_guard<std::mutex> lg(m);
		std::cout << "using shared data" << std::endl;

	} // <== 이 순간 unlock
	
	// 다른 코드들....
}

int main()
{
	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}



