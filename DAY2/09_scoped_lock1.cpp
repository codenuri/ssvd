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

// acc1 의 계좌 => acc2 의 계좌로 이체 하는 함수
void transfer(Account& acc1, Account& acc2, int cnt)
{
	// 2개의 계좌에 접근하므로 "독점권 획득"후 사용
	acc1.m.lock();
	acc2.m.lock();
	
    acc1.money -= cnt;
    acc2.money += cnt;
    std::cout << "finish transfer" << std::endl;

	acc2.m.unlock();
	acc1.m.unlock();
}

int main()
{
    Account kim, lee;
    std::jthread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::jthread t2(transfer, std::ref(lee), std::ref(kim), 5);
}

