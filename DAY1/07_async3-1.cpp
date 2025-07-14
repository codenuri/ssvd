#include <iostream>
#include <thread>
#include <chrono>
#include <future>
using namespace std::literals;

// 반환값

int add(int a, int b)
{
    std::cout << "A. start add" << std::endl; 
    std::this_thread::sleep_for(2s);
    std::cout << "B. finish add" << std::endl; 
    return a + b;
}

int main()
{
  	std::future<int> ft = std::async( std::launch::async, add, 10, 20);

    std::cout << "C. continue main " << std::endl; 

  	int ret = ft.get();

    std::cout << "D. finish main" << std::endl;	
}



