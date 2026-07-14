// 07_async3-1.cpp
#include <iostream>
#include <thread>
using namespace std::literals;

// std::async() 의 반환값을 받지 않으면 나타나는 현상을 설명하기 위한
// 문법 설명 코드
// 실제 future 클래스와는 완전히 다릅니다.
struct future
{
	bool release = false;

	void get() 
	{
		std::this_thread::sleep_for(5s);
		release = true;
	}
	// 소멸자가 핵심
	~future()
	{	
		if ( release == false)
			get();		
	}
};

// 함수가 값을 반환하면 임시객체로 반환 됩니다.
future async() 
{
	return future();
}

int main()
{
	// 함수가 반환한 임시객체는 함수 호출 문장의 끝에서 파괴 됩니다.
	async();
}