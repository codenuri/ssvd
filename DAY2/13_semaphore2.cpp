#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore>
using namespace std::literals;

// 뮤텍스   : 자원의 독점. 오직 한개의 스레드만 자원을 소유합니다.
// 세마포어 : 자원의 제한된 공유, N개의 스레드만 자원을 접근할수 있도록
//		     C++20 부터 사용가능

// #1. 전역변수로 생성
std::counting_semaphore<3> sem(3);	

void Download(std::string name)
{	
    sem.acquire(); // if ( --sem.count == 0 ) wait()

    for (int i = 0; i < 100; i++)
    {
        std::cout << name;
        std::this_thread::sleep_for(30ms);
    }
    std::cout << "\n finish " << name << std::endl;
    
	sem.release();
}

int main()
{
    std::jthread t1(Download, "1");
    std::jthread t2(Download, "2");
    std::jthread t3(Download, "3");
    std::jthread t4(Download, "4");
    std::jthread t5(Download, "5");
}
