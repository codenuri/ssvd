#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <numeric>

// "예제" 입니다.

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
    int s = std::accumulate(v2.begin(), v2.end(), 0);
    
	// 작업 #4. 작업#3의 결과를 출력합니다.
    std::cout << "\n" << s << std::endl;
}
// 위 코드는 4개의 작업을 순차적으로 진행합니다.
// 그런데, 작업#2 와 작업#3은 서로 독립적입니다. 동시에 진행해도 됩니다.
// 작업#4 는 반드시 작업#3이 종료되어야 할수 있습니다.
// => 작업 #3을 별도의 스레드로 작업해 봅시다.



