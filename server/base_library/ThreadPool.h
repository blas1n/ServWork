#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace ServWork
{
	class ThreadPool final
	{
	private:
		template <class RetType>
		using TaskRetType = std::enable_if_t<!std::is_void_v<RetType>, RetType>;

	public:
		static inline ThreadPool& Get() noexcept
		{
			static ThreadPool instance;
			return instance;
		}

		template <class Fn, class... Args>
		std::future<TaskRetType<std::invoke_result_t<Fn, Args...>>>
			AddTask(Fn&& fn, Args&&... args) noexcept
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

		template <class Fn, class... Args>
		void AddTask(Fn&& fn, Args&&... args) noexcept
		{
			auto task = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);

			taskMutex.lock();
			tasks.push(std::move(task));
			taskMutex.unlock();

			cv.notify_one();
		}

	private:
		ThreadPool();
		~ThreadPool();

		void ThreadWork() noexcept;

	private:
		std::vector<std::thread> threads;
		std::queue<std::function<void()>> tasks;
		std::condition_variable cv;
		std::mutex taskMutex;
		bool isEnd;
	};
}