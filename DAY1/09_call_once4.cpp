#include <iostream>
#include <thread>
#include <mutex>
using namespace std::literals;

// 이코드는 3번과 동일합니다.
// 주석 제거.

class Singleton
{
private:
    Singleton()
    {
        std::cout << "start ctor" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "finish ctor" << std::endl;
    }
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance()
    {
        static Singleton instance;
        return instance;
    }
};
void foo()
{
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();
    std::cout << &s1 << std::endl;
    std::cout << &s2 << std::endl;
}
int main()
{
    foo();
}



