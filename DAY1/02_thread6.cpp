#include <iostream>
#include <thread>

int main()
{
    std::thread t; // 생성자 인자로 함수 전달 안했습니다
				   // => 이 코드 자체는 아무 문제 없습니다
				   // => 단, 아직 스레드 생성 안되었습니다.

    t.join();	// 예외 발생. 아직 스레드가 생성되지 않았으므로

	std::cout << "main thread\n";
}
