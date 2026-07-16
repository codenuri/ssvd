#include <iostream>
#include <coroutine>
#include <utility>
#include <generator> 
#include <vector>

std::generator<int> foo()
{
    std::cout << "foo #1\n";
    co_yield 1;			

    std::cout << "foo #2\n";
    co_yield 2;
    
    std::cout << "foo #3\n";
}  

int main()
{
	std::vector<int> v = {1, 2, 3, 4, 5};

	for( auto e : v )
	{
		std::cout << e << '\n';
	}
	// 위 for 문의 원리를 생각해 봅시다.
}


