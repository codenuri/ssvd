// 15_pstl.cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <execution> // parallel stl 사용하려면 이 헤더 필요, C++17 이상

void foo(int n)
{
    std::cout << n << " : " << std::this_thread::get_id() << std::endl;
}
int main()
{
//  std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
 	std::vector<int> v(10000);

//  std::for_each(v.begin(), v.end(), foo); 
				  // A,       B,     함수
				  // => A ~ B 의 모든 요소를 함수에 전달해 달라.
				  // => 결국 주스레드가 foo 를 10번 호출

	// C++17 부터 "60여개의 알고리즘이 parallel 버전이 제공됩니다. "
	// => 어제 배운 "parallel_sum()" 같은 개념

    std::for_each(std::execution::par,   v.begin(), v.end(), foo);
	//			  ^ 이 인자가 외와 차이점.
}