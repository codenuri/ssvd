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

	t.join();
}


// 작업#3을 스레드로 하지말고, 작업 #2를 스레드로 하면 안되나요 ? promise 가 필요없지 않나요 ??
// => 화면 출력은 일반적으로 GUI 를 사용하는 경우가 많습니다.
// => 대부분의 GUI 프로그램에서 GUI 작업은 반드시 주스레드가 해야 합니다.
// => 모든 UI 는 스레드 소유인데, 대부분 UI 는 주스레드가 생성합니다.

// 핵심 : 위 코드에서 "람다표현식 부분" 을 일반 함수로 분리하면
// => std::v2, pro 등의 변수를 인자로 전달해야 합니다.
// => 인자가 많아지면 복잡해 집니다.
// => 위와 같은 작업은 람다 표현식이 좋습니다.

