#include <iostream>
#include <thread> // C++11 이후 제공, 
				  // 스레드 관련 라이브러리

// 빌드 방법 : g++ 01_this_thread1.cpp -std=c++20

// std::this_thread namespace 안에 있는 4개의 함수
// 1. std::this_thread::get_id()		: 현재 스레드의 ID 얻는 함수
// 2. std::this_thread::sleep_for()
// 3. std::this_thread::sleep_until()
// 4. std::this_thread::yield()			


int main()
{
	// 현재 스레드 ID 얻기
    std::cout << std::this_thread::get_id() << std::endl;

	// 주의 : ID 는 int 아님
	// std::thread 클래스 안에 id 라는 타입
    std::thread::id tid1 = std::this_thread::get_id();
	std::thread::id tid2 = std::this_thread::get_id();

	int n = std::this_thread::get_id(); // error. int 로 변환 안됨

	// 단, == 와 != 는 가능. 
	tid1 == tid2; // ok
	tid1 != tid2; // ok
}
/*
namespace std 
{
	class thread 
	{
		struct id 
		{			
		};
	}
}
*/