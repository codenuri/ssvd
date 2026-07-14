#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

// 핵심 : promise 를 사용하는 예제

int main()
{
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v2(10);

	// 작업 #1. v1 의 요소의 부분합을 v2 에 넣습니다.
    std::partial_sum(v1.begin(), v1.end(), v2.begin()); 

	// 작업 #2. v2 의 모든 요소 출력
    for (auto n : v2)
        std::cout << n << ", ";

	// 작업 #3. v2의 모든 요소를 더합니다
    int ret = std::accumulate(v2.begin(), v2.end(), 0);
    
	// 작업 #4. 작업 #3의 결과를 출력합니다.
    std::cout << "\n" << ret << std::endl;
}

// 위 코드는 총 4개의 작업 수행
// => #3이 완료되어야 #4가 실행가능하지만 
// => #2 와 #3 은 독립적인 작업 입니다
// => 2개를 동시에 실행해도 문제 되지 않습니다.



