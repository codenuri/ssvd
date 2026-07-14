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

// 함수가 값타입 반환하면 임시객체로 반환 됩니다.
future async() 
{
	return future();
}

int main()
{
	std::cout << "start main\n";
	// 함수가 반환한 임시객체는 함수 호출 문장의 끝에서 파괴 됩니다.
	// => 파괴 될때 소멸자 호출
	async();

	// 반환 값을 받으면
	// ret = 임시객체;   
	// => 임시객체의 내용을 ret 에 복사하고
	// => 임시객체 파괴 되는데.. 이때 소멸자가 호출되는데..요즘은 컴파일러 최적화로 소멸자 호출 제거
	// => 그런데, 실제 future 는 복사 생성자에서 임시객체를 release 같은 변수를 true 로 변경

	// => ret가 get() 하면 되므로 임시객체는 get()하지 말라는 것
	future ret = async();

	std::cout << "continue main\n";
}