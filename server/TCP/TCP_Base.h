#pragma once

#include "ThreadAccesser.h"
#include <functional>
#include <string>

class TCP_Base : protected ThreadAccesser
{
public:
	TCP_Base(int inPort, int inBufSize, int inQueueSize);
	TCP_Base(const std::string& configPath);

	TCP_Base(const TCP_Base& other) = delete;
	TCP_Base(TCP_Base&& other) noexcept;
	
	TCP_Base& operator=(const TCP_Base& other) = delete;
	TCP_Base& operator=(TCP_Base&& other) noexcept;
	
	~TCP_Base() override;

	inline int GetPort() const noexcept
	{
		return port;
	}

protected:
	char* buf;
	int queueSize;
	int bufSize;
	int port;
};