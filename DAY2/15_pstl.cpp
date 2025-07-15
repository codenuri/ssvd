// 15_pstl.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <execution>


void foo(int n)
{
    std::cout << n << " : " << std::this_thread::get_id() << std::endl;
}
int main()
{
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

    std::for_each(v.begin(), v.end(), foo); // 주스레드가 foo 함수를 10번 호출

//    std::for_each(std::execution::par, v.begin(), v.end(), foo);
}