#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <semaphore>
using namespace std::literals;

// 뮤텍스   : 자원의 독점.        소유자(lock()을 수행한 스레드)만이 unlock() 할수 있다.
// 세마포어 : 자원의 제한된 공유.  소유자 개념이 없다. 누구라도 카운트 증가 가능
std::counting_semaphore<3> sem(3);	


void Download(std::string name)
{	
    sem.acquire(); 

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

	std::this_thread::sleep_for(1s);

	// 주스레드는 세마포어를 acquire()하지 않았지만 카운트 증가 가능
	sem.release(); // ++sem.current_count;
}

// 정리
// mutex     : 한개 스레드가 자원 독점
// semaphore : N개  스레드가 자원 공유