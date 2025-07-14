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
	// 아래 예제는 std::async() 호출의 반환 값을 받았지만
	// => get() 을 호출 하지 않은 경우. 
  	std::future<int> ft = std::async( std::launch::async, add, 10, 20);

    std::cout << "C. continue main " << std::endl; 

//  int ret = ft.get(); // #1. 결과를 얻을때 까지 대기(2초) 합니다.
						//     결과를 얻은후 주스레드는 아래 코드를 실행하고 즉시 종료

    std::cout << "D. finish main" << std::endl;	

} // <= 이순간 지역변수인 ft 가 파괴 됩니다.
  // 1. ft 의 소멸자 ( ~future()) 가 호출됩니다.
  // 2. "ft.get()" 을 한번도 실행한 적이 없다면 소멸자에서 ft.get() 합니다
  // 3. 따라서 "D. finish main" 출력후 2초 뒤에 종료 됩니다.

  // => 그 이유는 
  // std::async 
  // 1. 사용자가 std::thread 객체를 생성후 join 하지 않고
  // 2. std::async 내부적으로 수행 
  // 3. join 하는 시점이 async 반환된 future 를 .get() 할때 입니다.
  // => 따라서 std::async 가 반환한 future 는 반드시 get() 을 해야 합니다.
  // => 사용자가 않아면 future 소멸자에서 수행. (위 결과 처럼)



