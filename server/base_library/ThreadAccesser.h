#pragma once

#include "ThreadPool.h"
#include <utility>

class ThreadAccesser
{
public:
	ThreadAccesser() = delete;
	~ThreadAccesser() = delete;

protected:
	template <class Fn, class... Args>
	static inline decltype(auto) AddTask(Fn&& fn, Args&&... args) noexcept
	{
		return threadPool->AddTask(std::forward(fn), std::forward(args)...);
	}

private:
	friend class ThreadPool;
	inline static ThreadPool* threadPool = nullptr;
}