#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

void do_work(unsigned id)
{}

int main()
{
	// do_work 를 실행하는 1 개의 스레드 만들기
	std::thread t(do_work, 3);

    // do_work 를 실행하는 10 개의 스레드 만들기

	// #1. 아래 처럼 하면 thread 객체 변수를 관리할수 없습니다. - 잘못된 코드
	/*
	for(int i = 0; i < 10; i++)
	{
		std::thread t(do_work, 3); // {} 벗어날때 t 파괴!!
	}
	*/

	// #2. vector 를 사용한 관리
	std::vector<std::thread> v; // 아직 크기가 없는 vector

	for( int i = 0; i < 10; i++ )
	{
		std::thread t(do_work, 3);

		v.push_back(t); 
	}
}
