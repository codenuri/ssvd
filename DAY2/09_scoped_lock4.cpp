#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;
// 은행 계좌
struct  Account
{
	std::mutex m;
    int money = 100;
};

void transfer(Account& acc1, Account& acc2, int cnt)
{	
	// C++14 까지 : 함수   템플릿의 타입 인자는 생략 가능
	//              클래스 템플릿의 타입 인자는 생략 할수 없다.
//	std::scoped_lock<std::mutex, std::mutex> g(acc1.m, acc2.m);

	// C++17 이후 : 클래스 템플릿의 타입 인자도 생략 가능(단, 생성자 인자로 추론 가능한 경우만)
	//				그래서 아래 처럼 사용가능. 
	std::scoped_lock g(acc1.m, acc2.m);	 // acc1.m 과 acc2.m 의 타입이 달라도 됩니다.
										 // 컴파일러가 알아서 추론

	// std::lock_guard, std::unique_lock, std::shared_lock, 
	// std::vector 등도 모두 생략 가능
//	std::vector<int> v = {1,2,3}; // C++14 까지
//	std::vector      v = {1,2,3}; // C++17 이후

//	std::lock_guard<std::mutex> g(m); // C++14 까지
//	std::lock_guard             g(m); // C++17 이후

	acc1.money -= cnt; 
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;
}

int main()
{
    Account kim, lee;
    std::jthread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::jthread t2(transfer, std::ref(lee), std::ref(kim), 5);
}

