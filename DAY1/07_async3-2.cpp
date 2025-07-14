#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// 반환값

int add(int a, int b)
{
    std::cout << "A. start add" << std::endl; 
    std::this_thread::sleep_for(2s);
    std::cout << "B. finish add" << std::endl; 
    return a + b;
}



int main()
{
	// std::async 의 반환값을 받지 않았을때
	// => 1. 반환된 리턴 값은 임시객체로 입니다.(아래 async 구현 참고)
	// => 2. 임시객체는 함수 호출 문장 끝에서 파괴 됩니다.
	// => 3. 소멸자 호출되고 get() 을 하게 되므로 2초간 대기후, 다음 문장 실행
	// => 그래서, 마치 동기호출처럼 보이게 됩니다.

	// 결론 : std::async 사용시 반드시 반환 값을 받으세요.
	//       그리고, 꼭 get() 하세요. => 이코드가 join() 의 효과
  	std::async( std::launch::async, add, 10, 20);

    std::cout << "C. continue main " << std::endl; 

    std::cout << "D. finish main" << std::endl;	
} 

/*
std::future async(...)
{
	return std::future(...); // 함수가 값 타입으로 반환하면 임시객체로 반환됨.
}
*/
