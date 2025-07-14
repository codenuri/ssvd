#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

	std::promise<int> pro;
	std::future<int> ft = pro.get_future();

	// 작업 #1. v1 의 요소의 부분합을 v2 에 넣습니다.
    std::partial_sum(v1.begin(), v1.end(), v2.begin()); 

	//-------------------------------------------------------
	// 핵심 : 람다 표현식을 실행하는 스레드를 만들어서 "작업 #3"을 수행
//	std::thread t([&v2, &pro]() 
	std::thread t([&]() 					// 모든 지역변수를 레퍼런스로 캡쳐
	{  
		// 작업 #3. v2의 모든 요소를 더합니다
    	int s = std::accumulate(v2.begin(), v2.end(), 0);

		pro.set_value(s);
	});
	//---------------------------------------------------

	// 작업 #2. v2 의 모든 요소 출력
    for (auto n : v2)
        std::cout << n << ", ";
    
	// 작업 #4. 작업#3의 결과를 출력합니다.
	int ret = ft.get();
    std::cout << "\n" << ret << std::endl;
}



