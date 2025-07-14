#include <iostream>
#include <thread>

int main()
{
    std::thread t; // 생성자 인자로 함수 전달 안했습니다
				   // => 이 코드 자체는 아무 문제 없습니다
				   // => 단, 아직 스레드 생성 안되었습니다.

//  t.join();	// 예외 발생. 아직 스레드가 생성되지 않았으므로

	// 해결책 #1. 예외 처리
	/*
	try 
	{
		t.join();
	}
	catch(std::exception& e)
	{
	}
	*/
	// 해결책 #2. 조사후 사용
	if ( t.joinable() ) // 현재 대기 가능한 스레드가 있다면
	{
		t.join();
	}
	else 
		std::cout << "현재 대기 가능한 스레드 없음\n";


	std::cout << "main thread\n";
}
