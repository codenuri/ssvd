#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

// 10개의 스레드 만들기
// 핵심은 "vector" 로 std::thread 객체의 관리

void do_work(unsigned int id)
{}

int main()
{
    // create.. 10 thread
	// => 각 스레드에 대해서 join 해야 하므로 t 객체를 관리해야 한다.

	// #1. 초기 크기가 없는 vector 사용
	std::vector<std::thread> v1;

	for( int i = 0; i < 10; i++)
	{
		// 1. 스레드 객체를 생성한후 push_back 사용 - 반드시 std::move 로 전달
//		std::thread t(&do_work, i); 
//		v1.push_back(t); // error. t 자체가 아닌 t의 복사본 보관.
						 // std::thread 는 복사 될수 없다.
//		v1.push_back(std::move(t)); // ok 

		// 2. 임시객체로 생성해서 push_bck
		v1.push_back( std::thread(&do_work, i) );
	}
	//....

	// v1 vector 에 있는 모든 thread 에 대해서 join
	for( auto& t : v1)
		t.join();
	
	// #2. 필요한 크기 만큼을 미리 생성하는 vector(또는 배열)
	// => std::thread 객체만 10개 생성되었고, 
	// => 아직 스레드 자체는 생성 안됨
	std::vector<std::thread> v2(10); // "std::thread v2[10]" 처럼 배열도 가능. 

	for(int i = 0; i < 10; i++)
	{
		v2[i] = std::thread(&do_work, i); // 임시객체 형태로 넣으므로
										  // 대입 연산자가 아닌, move 대입 연산자
										  // ok
	}

	// thread7.cpp, thread8.cpp 예제의 핵심은 "위 코드를 이해 하기 위한 것"
	for( auto& t : v2)
		t.join();
}
