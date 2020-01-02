#include "ThreadPool.h"
#include <utility>
#include "Core.h"
#include "Name.h"

namespace ServWork
{
	ThreadPool::ThreadPool()
		: threads(), tasks(), cv(), taskMutex(), isEnd(false)
	{
		if (isCreated)
			throw MakeError("thread_pool_is_already_created");

		isCreated = true;

		auto threadNum = std::thread::hardware_concurrency();
		if (threadNum == 0)
			throw MakeError("hardware_concurrency_is_0");

		threads.reserve(threadNum * 2 + 1);

		while (threadNum--)
			threads.emplace_back([this]() { ThreadWork(); });
	}

	ThreadPool::~ThreadPool()
	{
		isEnd = true;
		cv.notify_all();

		for (auto& t : threads)
			t.join();

		isCreated = false;
	}

	void ThreadPool::ThreadWork() noexcept
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock{ taskMutex };
			cv.wait(lock, [this]() { return !tasks.empty() || isEnd; });
			if (isEnd && tasks.empty()) return;

			auto&& task = std::move(tasks.front());
			tasks.pop();
			lock.unlock();
			task();
		}
	}
}