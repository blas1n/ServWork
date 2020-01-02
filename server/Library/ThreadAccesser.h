#pragma once

#include "ThreadPool.h"
#include <utility>

namespace ServWork
{
	class ThreadAccesser
	{
	protected:
		ThreadAccesser() = default;
		~ThreadAccesser() = default;

		template <class Fn, class... Args>
		static decltype(auto) AddTask(Fn&& fn, Args&&... args) noexcept
		{
			return threadPool->AddTask(std::forward(fn), std::forward(args)...);
		}

	private:
		friend class ThreadPool;
		inline static ThreadPool* threadPool = nullptr;
	};
}