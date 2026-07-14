#include <chrono>
#include <iostream>
#include <thread>
using namespace std::literals;

// std::jthread 의 특징
// 1. 자동 join() 기능
// 2. cooperative cancelation(협력적 취소) 를 지원
//	  


void foo( std::stop_token token )
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "foo : " << i << std::endl;

		if ( token.stop_requested() )
		{
			std::cout << "receive stop_requsted\n";
			break;
		}
    }
	std::cout << "finish foo\n";
}

// 핵심 : goo 는 인자 없음
void goo( )
{
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(500ms);
        std::cout << "goo : " << i << std::endl;
    }
	std::cout << "finish foo\n";
}


int main()
{
	// 핵심 : jthread 는 인자로 함수만 받을뿐, 추가적인 데이타는 없습니다.
	// => 하지만 foo 에 자동으로 stop_token 전달
    std::jthread t(foo);
	std::jthread t1(goo); // goo 는 인자가 없으므로 stop_token 전달 안됨
    
    std::this_thread::sleep_for(2s);

	t.request_stop();   // 스레드에게 종료 요청
	t1.request_stop();  // 에러는 아님. 하지만 아무런 효과 없음. goo 는 stop_token 인자 없음. 

//	t.join();	// jthread 이므로 필요없음
}