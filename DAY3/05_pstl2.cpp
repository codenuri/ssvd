#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
#include <execution>
#include <syncstream>

void foo(int n)
{
    std::osyncstream out(std::cout);
    out << "[" << std::this_thread::get_id() << "]: " << n << '\n';
}

int main()
{
    std::vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

	int s = 0;
  	std::for_each(v.begin(), v.end(), [&s](int n) { s += n;}); 

	std::cout << "result: " << s << '\n';

}
