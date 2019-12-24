#pragma once

#include <functional>
#include <string>

class Base_TCP
{
public:
	Base_TCP(class ThreadPool& inThreadPool);
	virtual ~Base_TCP();

	inline int GetPort() const noexcept
	{
		return port;
	}

protected:
	ThreadPool& threadPool;
	char* buf;
	int queueSize;
	int bufSize;
	int port;

private:
	inline static const std::string ConfigDir = "../config.ini";
};