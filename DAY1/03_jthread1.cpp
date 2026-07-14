#include <iostream>
#include <thread>

// join_thread 

class scoped_thread 
{
	std::thread t;
public:
	scoped_thread(std::thread th) : t(std::move(th)) {} 

	~scoped_thread()
	{
		if ( t.joinable() )
			t.join();
	}
};


void foo(int a, int b)
{
	std::cout << "foo : " << a << ", " << b << std::endl;
}

int main()
{
	// #1. std::thread 사용시, 반드시 종료되기 전에 join() 또는 detach() 해야 합니다
//  std::thread t1(&foo, 10, 20);
// 	t1.join();

	// #2. 많은 C++ 개발자들이 위에 있는 scoped_thread 같은 클래스를 만들어서 사용했습니다.
	// => 장점 : st 의 소멸자에서 자동으로 join() 하므로 명시적 join() 호출 필요 없음. 
//	scoped_thread st( std::thread(&foo, 10, 20) );

	// #3. C++ 20 에서 scoped_thread 와 유사한 jthread 가 표준에 추가됨.
	// => t의 소멸자에서 자동으로 join() 실행!
	std::jthread t(&foo, 10, 20);

	// t.join() 필요없음. 
	// t.detach()  <= 필요하면 명시적 호출 가능 
}


