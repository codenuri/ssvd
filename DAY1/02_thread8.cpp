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
		// #1. 스레드 객체를 생성후 move 로 push
//		std::thread t(do_work, 3);
//		v.push_back(t); // error. t 를 복사한 복사본을 보관 하는 코드, std::thread 는 복사 안됨
//		v.push_back(std::move(t)); // ok. 이동은 가능

		// #2. temporary 형태로 push
//		v.push_back( std::thread(do_work, 3) ); // ok

		// #3. emplace_back 사용 - 가장 널리 사용. 권장, 강의에서도 이렇게
		// => std::vector 사용시 emplace_back() 은 너무나 중요.. 반드시 학습해 두세요
		// => push_back( 인자가 객체 )
		//    emplace_back( 객체를 만들기 위한 생성자만 전달)
//		v.push_back( std::thread(do_work, 3) ); // std::thread 객체를 전달
		v.emplace_back( do_work, 3 ); // std::thread 생성에 필요한 인자만 전달
	}

	// join 필요
	for( auto& t : v) // "std::thread& t : v" 
		t.join();
}
