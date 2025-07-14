#include <iostream>
#include <thread>
#include <chrono>
using namespace std::literals;

void foo()
{
	for ( int i = 0; i < 10; i++ )
	{
    	std::cout << "foo : " << i << std::endl;
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
    std::thread t1(&foo);

    t1.join();
}

