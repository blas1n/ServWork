#if PLATFORM_LINUX

#pragma once

#include "Base_TCP.h"

class TCP_Linux final : public Base_TCP
{
public:
	TCP_Linux(int inPort, int inBufSize, int inQueueSize);
	TCP_Linux(const std::string& configPath);

	TCP_Linux(TCP_Linux&& other) noexcept;
	TCP_Linux& operator=(TCP_Linux&& other) noexcept;

	~TCP_Linux() override;

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

private:
	void Init();

private:
	std::function<void(int, char*)> onAccept;
	int serverSocket;
};

using TCP = TCP_Linux;

#endif