#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std::literals;

std::mutex m;
int shared_data = -1; // 아직 데이타 없음.

// 아래 코드는 공유자원을 동기화 하기 위해 뮤텍스를 사용합니다.
// => 공유 자원에 대한 "동시접근" 문제는 해결

// 남은 문제점은
// => 생산자가 생산하기 전에 소비자가 먼저 도착하면
//    잘못된 데이타를 사용하게 됩니다

// => 생산자가 생산할때 까지 소비자를 대기할수 없을까요 ?
//    => "std::condition_variable" 사용
void consumer()
{
    std::lock_guard<std::mutex> lg(m);
    std::cout << "consume : " << shared_data << std::endl;
}
void producer()
{
    std::this_thread::sleep_for(10ms);
    std::lock_guard<std::mutex> lg(m);
    shared_data = 100;
    std::cout << "produce : " << shared_data << std::endl;
}
int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); 
    t2.join();
}