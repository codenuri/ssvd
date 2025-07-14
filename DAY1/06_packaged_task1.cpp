#include <iostream>
#include <thread>
#include <future>

/*
void add(std::promise<int>&& p, int a, int b)
{
	p.set_value(a + b);
}
*/

int add(int a, int b)
{
	return a + b;
}



int main()
{
	std::promise<int> pm;
	std::future<int> ft = pm.get_future();

	std::thread t(add, std::move(pm), 10, 20);

	int ret = ft.get();

	t.join();
}



