#include <iostream>
#include <thread>

// join_thread 

void foo(int a, int b)
{
	std::cout << "foo : " << a << ", " << b << std::endl;
}

// std::thread 를 직접 사용하면 사용후 반드시 join() 해야 합니다
// => 아래 클래스를 생각해 보세요
class scoped_thread 
{
	std::thread t;
public:
	scoped_thread(std::thread th) : t(std::move(th)) {} 

	// 아래 소멸자가 핵심 
	// => 결국 소멸자에서 자동 join()되는 클래스
	// => C++20 나오기 전까지 많은 개발자가 즐겨 사용하던 유명한 기술..
	~scoped_thread()
	{
		if ( t.joinable() )
			t.join();
	}
}

int main()
{
//  std::thread t1(&foo, 10, 20);
//	t1.join();

	scoped_thread st( std::thread(&foo, 10, 20) );
}

