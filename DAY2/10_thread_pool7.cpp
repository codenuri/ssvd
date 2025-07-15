#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
using namespace std::literals;

// 핵심 
// ThreadPool::pool_add 를 가변인자 템플릿으로
// => 인자의 갯수와 타입이 상관없이 모든 종류의 함수가 가능하도록
// 

class ThreadPool
{
	using TASK = std::function<void()>;

	std::queue<TASK> task_q;
	std::mutex q_guard;
	std::condition_variable cv;
	bool stop = false;
	std::vector<std::thread> v;
public:
	ThreadPool(std::size_t size)
	{
		for (int i = 0; i < size; i++)
			v.emplace_back(std::bind(&ThreadPool::pool_thread_main, this));
	}

	~ThreadPool()
	{
		{
			std::lock_guard<std::mutex> lg(q_guard);
			stop = true;
		}
		cv.notify_all();

		for (std::thread& t : v)
			t.join();
	}

	void pool_thread_main()
	{
		while (1)
		{
			TASK task;
			{
				std::unique_lock<std::mutex> ul(q_guard);
				cv.wait(ul, [this] { return stop || !task_q.empty(); });

				if (stop && task_q.empty())
					return;

				task = task_q.front();
				task_q.pop();
			}
			task();
		}
	}

	template<typename F, typename ... ARGS>
	decltype(auto) pool_add(F&& f, ARGS&& ... args)
	{
		using return_type = decltype(std::forward<F>(f)(std::forward<ARGS>(args)...));

		auto p = std::make_shared<std::packaged_task<return_type()>>(
			std::bind(std::forward<F>(f), std::forward<ARGS>(args)...));

		std::future<return_type> res = p->get_future();

		{
			std::lock_guard<std::mutex> lg(q_guard);

			task_q.push([p] { (*p)(); });
		}
		cv.notify_one();

		return res;
	}

};








int foo(int a, int b)
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "foo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
	return 10;
}
double goo(int a, int b, double c)
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "		goo : " << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(400ms);
	}
	return 3.4;
}

int main()
{
	ThreadPool pool(10);

	std::future<int>    ft1 = pool.pool_add(foo, 1, 2);
	std::future<double> ft2 = pool.pool_add(goo, 1, 2, 3.4);

	// 반환 타입은 아래처럼 auto로 하면 됩니다.
	auto ft3 = pool.pool_add(goo, 0, 0, 3.4);


	int ret1 = ft1.get();

	std::cout << ret1 << std::endl;
}
