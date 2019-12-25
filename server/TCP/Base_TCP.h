#pragma once

#include "ThreadAccesser.h"
#include <functional>
#include <string>

class Base_TCP : protected ThreadAccesser
{
public:
	Base_TCP(int inPort, int inBufSize, int inQueueSize);
	Base_TCP(const std::string& configPath);

	Base_TCP(const Base_TCP& other) = delete;
	Base_TCP(Base_TCP&& other) noexcept;
	
	Base_TCP& operator=(const Base_TCP& other) = delete;
	Base_TCP& operator=(Base_TCP&& other) noexcept;
	
	~Base_TCP() override;

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