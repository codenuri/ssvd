#include <iostream>
#include <string_view>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

// 공유 자원을 사용하는 시간이 짧다면
// => mutex 를 사용하지 말고..
// => 무한루프(CPU를 사용) 하면서 공유 자원을 획득하기 위해 시도

bool use_flag = false;

void work(std::string_view name)
{	
	// 공유 자원이 사용중이면 계속 대기
	// => CPU 를 사용하면서 대기 하므로 "busy waiting" 이라고 합니다.
	// => 이기술은 공유 자원 사용시간이 짧은 경우만 사용해야 합니다
	// => 회전(루프)를 하면서 lock 을 시도 하므로 "spin lock" 이라는 용어도 사용

	// 단, 아래 코드는 전역변수를 동기화 없이 사용하므로 버그!!
	// => 다음 소스에서 해결
	while(use_flag);

	std::cout << "using shared resource " << name << std::endl;

	use_flag = false;	// 공유 자원 사용 종료!
}




int main()
{
	std::jthread t1(work, "A");
	std::jthread t2(work, "B");
	std::jthread t3(work, "C");

}