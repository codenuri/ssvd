#include <iostream>
#include <thread>

// join(), exception 이야기

int main()
{
    std::thread t; 	// 생성자 인자 함수 전달 안함
					// thread 생성 안됨

//  t.join();		// exception 발생. 
					// thread 가 생성된 적이 없는데 join()/detach()사용

	// #1. try~catch
	try 
	{
		t.ioin();
	}
	catch( std::exception& e) 
	{
		// ....
	}

	// #2. check joinable() 
	// => 스레드를 생성하지 않았거나, 이미 join()된 경우
	//    joinable()은 false 반환
	if ( t.joinable() )	
		t.join();
}
