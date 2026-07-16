#include <iostream>
#include <string_view>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;

void work(std::string_view name)
{	
	// 함수 안에서 공유 자원을 사용하고
	// 여러개 스레드가 이 함수를 실행하게 된다면
	// "공유 자원을 동기화 해야 합니다"
	// 아래 코드는 mutex 사용 했으므로 안전 합니다

	// mutex 사용시
	// => lock() 을 획득하지 못한 스레드는 대기 상태에 빠지게 됩니다.
	//    대기 상태에 들어가는 것도 시간 소요

	// => 그런데, 공유 자원을 사용하는 시간이 아주 짧다면.. 대기 상태 빠지기 전에 종료도 가능
	// => 이경우 mutex 는 비효율적..
	// => 다음 소스에서 해결

	std::lock_guard<std::mutex> g(m);
	std::cout << "using shared resource " << name << std::endl;
}

int main()
{
	std::jthread t1(work, "A");
	std::jthread t2(work, "B");
	std::jthread t3(work, "C");

}