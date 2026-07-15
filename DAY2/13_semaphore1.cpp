#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore>
using namespace std::literals;

// 뮤텍스 : 자원의 독점. 오직 한개의 스레드만 자원을 소유합니다.
std::mutex m;

// 인터넷에서 다운로드 하는 프로그램을 생각해 봅시다.
void Download(std::string name)
{
	// 뮤텍스를 사용했으므로
	// => 오직 스레드 한개씩만 다운로드 가능합니다.
	// => 스레드가 종료되면 다른 스레드 다운로드 가능
    m.lock();

    for (int i = 0; i < 100; i++)
    {
        std::cout << name;
        std::this_thread::sleep_for(30ms);
    }
    std::cout << "\n finish " << name << std::endl;
    
	m.unlock();
}

int main()
{
    std::jthread t1(Download, "1");
    std::jthread t2(Download, "2");
    std::jthread t3(Download, "3");
    std::jthread t4(Download, "4");
    std::jthread t5(Download, "5");
}

// 한개의 독점이 아닌
// 제한된 갯수 만큼 공유 할수 없을까요 ?

// => 3개의 스레드 까지는 다운로드 허용
// => C++20 에서 추가된 세마포어 사용
// => 다음소스