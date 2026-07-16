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

}


