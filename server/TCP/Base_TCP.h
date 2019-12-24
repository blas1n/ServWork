#pragma once

#include "ThreadAccesser.h"
#include <functional>
#include <string>

class Base_TCP : protected ThreadAccesser
{
public:
	Base_TCP();

	Base_TCP(const Base_TCP& other);
	Base_TCP(Base_TCP&& other) noexcept;
	
	Base_TCP& operator=(const Base_TCP& other);
	Base_TCP& operator=(Base_TCP&& other) noexcept;

	virtual ~Base_TCP();

	inline int GetPort() const noexcept
	{
		return port;
	}

protected:
	char* buf;
	int queueSize;
	int bufSize;
	int port;

private:
	inline static const std::string ConfigDir = "../config.ini";
};