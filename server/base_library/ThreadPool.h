#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool
{
public:
	ThreadPool();
    ~ThreadPool();

	template <class Fn, class... Args>
	std::future<std::invoke_result_t<Fn, Args...>> AddTask(
		Fn&& fn, Args&&... args) noexcept;

private:
	void ThreadWork() noexcept;

private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;
	std::condition_variable cv;
	std::mutex taskMutex;
	bool isEnd;
};

template <class Fn, class... Args>
std::future<std::invoke_result_t<Fn, Args...>> ThreadPool::AddTask(Fn&& fn, Args&&... args) noexcept
{
	auto task = std::make_shared<
		std::packaged_task<std::invoke_result_t<Fn, Args...>()>>(
			std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...)
	);

	taskMutex.lock();
	tasks.push([task] { (*task)(); });
	taskMutex.unlock();

	cv.notify_one();
	return task->get_future();
}
