#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::literals;

struct  Account
{
	std::mutex m;
    int money = 100;
};

void transfer(Account& acc1, Account& acc2, int cnt)
{
	// 2개 이상의 뮤텍스를 lock 할때는 절대 아래 처럼 하면 안됩니다.
	// acc1.m.lock();
	// acc2.m.lock();

	// "deadlock 회피 알고리즘" 으로 작성된 함수를 사용해야 합니다
	// std::lock(mutex1, mutex2, mutex3....) : 여러개 뮤텍스를 안전하게 lock 해달라.
	std::lock(acc1.m, acc2.m);

    acc1.money -= cnt;
    acc2.money += cnt;

	acc1.m.unlock();
	acc2.m.unlock();

    std::cout << "finish transfer" << std::endl;
}

int main()
{
    Account kim, lee;
    std::thread t1(transfer, std::ref(kim), std::ref(lee), 5);
    std::thread t2(transfer, std::ref(lee), std::ref(kim), 5);
    t1.join();
    t2.join();
}

