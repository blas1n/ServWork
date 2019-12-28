#pragma once

#include "Socket.h"
#include <functional>
#include <string>

class TCP
{
public:
	TCP(int inPort, int inBufSize, int inQueueSize);
	TCP(const std::string& configPath);

	TCP(const TCP& other) = delete;
	TCP(TCP&& other) noexcept;
	
	TCP& operator=(const TCP& other) = delete;
	TCP& operator=(TCP&& other) noexcept;
	
	~TCP();

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

	inline int GetPort() const noexcept
	{
		return port;
	}

	inline int GetBufferSize() const noexcept
	{
		return bufSize;
	}

	inline int GetQueueSize() const noexcept
	{
		return queueSize;
	}

private:
	void Init(int inPort, int inBufSize, int inQueueSize);

private:
	std::function<void(Socket, std::byte*)> onAccept;

	Socket s;
	std::byte* buf;
	int queueSize;
	int bufSize;
	int port;
};