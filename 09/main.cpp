#include <iostream>
#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
	bool keep_working;
	std::vector<std::thread> treads;
	std::queue<std::packaged_task<void()>> tasks;
	std::mutex mut_;
	std::condition_variable con_var_;

public:
	explicit ThreadPool(size_t size);
	~ThreadPool();

	template<typename Func, typename... Args>
	auto exec(Func func, Args ... args);
	template <typename Func>
	auto exec(Func func);

private:
	void InitFunc();
};

ThreadPool::ThreadPool(size_t size)
	: keep_working(true)
{
	for (size_t i = 0; i < size; ++i)
	{
		treads.emplace_back(&ThreadPool::InitFunc, this);
	}
}

void ThreadPool::InitFunc()
{
	std::packaged_task<void()> task;
	while (keep_working)
	{
		{
			std::unique_lock<std::mutex> lock(mut_);
			con_var_.wait(lock, [this]() { return !tasks.empty(); });
			if (!keep_working)
				return;
			task = std::move(tasks.front());
			tasks.pop();
			task();
		}
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::lock_guard<std::mutex> lock(mut_);
		keep_working = false;
	}
	con_var_.notify_all();

	for (auto &&t : treads)
	{
		t.join();
		//t.detach();
	}
}

template <class Func, class... Args>
std::packaged_task<void()> makeTask(Func f, Args&&... args)
{
	return std::packaged_task<void()>(
		[=]()
	{
		return f(args...);
	});
}

template <class Func>
std::packaged_task<void()> makeTask(Func f)
{
	return std::packaged_task<void()>(
		[=]()
	{
		return f();
	});
}


template <typename Func, typename... Args>
auto ThreadPool::exec(Func func, Args ... args)
{	
	std::packaged_task<decltype(func(args...))()> task(std::bind(func, args...));
	//auto task = makeTask(func, args...);

	auto future = task.get_future();
	//tasks.push(makeTask(std::move(task)));
	{
		std::lock_guard<std::mutex> lock(mut_);
		tasks.push(std::packaged_task<void()>(std::move(task)));
		//tasks.push(makeTask(func, args...));
	}
	con_var_.notify_one();

	return future;
}

template <typename Func>
auto ThreadPool::exec(Func func) 
{
	std::packaged_task<decltype(func())()> task(func);
	auto future = task.get_future();
	{
		std::lock_guard<std::mutex> lock(mut_);
		tasks.emplace(std::packaged_task<void()>(std::move(task)));
	}
	con_var_.notify_one();

	return future;
}


struct A 
{
	A(int x_, int y_) : x(x_), y(y_) {}
	int x;
	int y;
};

int foo(const A& a) 
{
	int z = a.x + a.y;
	return z;
}

bool test()
{
	ThreadPool pool(8);
	for (int i = 0; i < 9; ++i)
	{
		if (i % 2 == 0)
		{
			auto res = pool.exec(foo, A(1, 2));
			if (res.get() != 3)
				return false;
			std::cout << "this is " << i << " func" << std::endl;
		}
		if (i % 2 == 1)
		{
			auto res = pool.exec([]() { return 1; });
			if (res.get() != 1)
				return false;
			std::cout << "this is " << i << " func" << std::endl;
		}
	}
	return true;
}

int main() 
{
	if (!test())
	{
		std::cout << "Test failed!" << std::endl;
		return 1;
	}
	std::cout << "All test completed!" << std::endl;
	return 0;
}