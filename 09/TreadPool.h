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

template <typename Func, typename... Args>
auto ThreadPool::exec(Func func, Args ... args)
{
	std::packaged_task<decltype(func(args...))()> task(std::bind(func, args...));

	auto future = task.get_future();
	{
		std::lock_guard<std::mutex> lock(mut_);
		tasks.push(std::packaged_task<void()>(task));
	}
	con_var_.notify_one();

	return future;
}

