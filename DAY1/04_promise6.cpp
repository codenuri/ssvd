#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

// 스레드가 하는 일이 간단한 경우는
// => 아래 처럼 일반 함수로 하지 말고 람다 표현식이 좋습니다.
// => 일반 함수의 경우, 인자로 데이터를 많이 전달 받게되면 코드가 복잡해 집니다.
/*
void work2(std::vector<int>& v, std::promise<int>& pro)
{
	int ret = std::accumulate(v.begin(), v.end(), 0);
	pro.set_value(ret);

	// ... 추가적인 마무리 작업
}
*/


int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

	// 작업 #1. 
    std::partial_sum(v1.begin(), v1.end(), v2.begin()); 


	// 작업 #3은 별도의 스레드로
	std::promise<int> pro;
	std::future<int> ft = pro.get_future();

//	std::jthread t( work2, std::ref(v2), std::ref(pro)  );

	// 일반 함수 대신 람다 표현식을 사용하면
	// 1. 코드 흐름을 읽기 쉬워 집니다.
	//    => main 함수 안에 스레드 구현 코드도 같이 구현

	// 2. main 안에서 만든 지역변수 접근이 쉬워 집니다. 
	// => 인자로 전달하는 것이 아니라, 람다 지역변수 캡쳐 문법
	std::jthread t( [&v2, &pro]() { 
				int ret = std::accumulate(v2.begin(), v2.end(), 0);
				pro.set_value(ret);
			}  );


	// 작업 #2.
    for (auto n : v2)
        std::cout << n << ", ";

	// 다음 작업전에, 스레드가 수행중인 작업의 결과 대기 
    int ret = ft.get();

	// 작업 #4.
    std::cout << "\n" << ret << std::endl;
}




