#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

// 핵심 : promise 를 사용하는 예제

void work2(std::vector<int>& v, std::promise<int>& pro)
{
	int ret = std::accumulate(v.begin(), v.end(), 0);

	pro.set_value(ret);

	// ... 추가적인 마무리 작업
}

int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

	// 작업 #1. v1 의 요소의 부분합을 v2 에 넣습니다.
    std::partial_sum(v1.begin(), v1.end(), v2.begin()); 

	// 스레드를 생성해서 #3 작업을 수행하게 하고
	// 주스레드는 #2 작업 실행
	// 스레드 함수인 work2 는 
	// => "v2" 를 참조로 받아야 하고
	// => 연산의 종료를 알리기 위해 promise 등도 필요 합니다.
	std::promise<int> pro;
	std::future<int> ft = pro.get_future();

	std::thread t( work2, std::ref(v2), std::ref(pro)  );


	// 작업 #2. v2 의 모든 요소 출력
    for (auto n : v2)
        std::cout << n << ", ";

	// 주 스레드는 #2 작업완료후에는 #4 를 위해서
    // => 새로운 스레드가 작업이 종료되었는지 대기 해야 합니다 (결과도 필요)
    int ret = ft.get();

	// 작업 #4. 작업 #3의 결과를 출력합니다.
    std::cout << "\n" << ret << std::endl;
}




