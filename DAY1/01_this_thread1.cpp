#include <iostream>
#include <thread>	// C++11 에서 표준에 추가된 헤더.

// std::this_thread namespace 안에 있는 4개의 함수
// 1. std::this_thread::get_id()
// 2. std::this_thread::sleep_for()
// 3. std::this_thread::sleep_until()
// 4. std::this_thread::yield()			


int main()
{
	// 현재 스레드 ID 얻기 
    std::cout << std::this_thread::get_id() << std::endl;

	// 스레드 ID 는 정수 타입 아닙니다.
	// => int 타입과 호환(암시적 변환) 안됩니다
    std::thread::id tid1 = std::this_thread::get_id();
	auto tid2 = std::this_thread::get_id();

}