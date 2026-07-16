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

bool use_flag = true;

void work(std::string_view name)
{	
	// 공유 자원이 사용중이면 계속 대기
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