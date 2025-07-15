#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;

/*
void work()
{
	m.lock(); 	// 늦게 도착한 스레드는 대기 해야 합니다.(OS 관점에서 active list 에서 wait list 로 이동)

	// 그런데, 아래 작업이 아주 빨리 종료 된다면
	// => 대기 리스트로 옮기는 작업중에 벌써 unlock 될수 있습니다.
	std::cout << "start. using shared resource" << std::endl;
	std::cout << "end.   using shared resource" << std::endl;

	m.unlock();
}
*/

// 임계영역에서 하는 작업이 아주 간단하다면 "mutex" 보다 아래 처럼 "busy waiting" 이 좋습니다.
// 그런데, 아래 코드 처럼 사용하려면
// => "wait_flag" 전역변수가 다시 동기화 되어야 합니다.
// => bool 이 아닌 std::atomic<bool> 사용
bool wait_flag = false;

void work()
{
	while( wait_flag );
	wait_flag = true;

	std::cout << "start. using shared resource" << std::endl;
	std::cout << "end.   using shared resource" << std::endl;

	wait_flag = false;
}

 
int main()
{
	std::thread t1(work), t2(work);

	t1.join();
	t2.join();
}