#pragma once

#include "ThreadPool.h"
#include <utility>

class ThreadAccesser
{
public:
	virtual ~ThreadAccesser() = default;

protected:
	template <class Fn, class... Args>
	static inline decltype(auto) AddTask(Fn&& fn, Args&&... args) noexcept
	{
		return threadPool->AddTask(std::forward<Fn>(fn), std::forward<Args>(args)...);
	}

private:
	friend class ThreadPool;
	inline static ThreadPool* threadPool = nullptr;
}