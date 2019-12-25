#if PLATFORM_WINDOWS

#pragma once

#include "Base_TCP.h"
#include <WinSock2.h>

class Windows_TCP final : public Base_TCP
{
public:
	Windows_TCP(int inPort, int inBufSize, int inQueueSize);
	Windows_TCP(const std::string& configPath);

	Windows_TCP(Windows_TCP&& other) noexcept;
	Windows_TCP& operator=(Windows_TCP&& other) noexcept;

	~Windows_TCP() override;

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

private:
	void Init();

private:
	std::function<void(SOCKET, char*)> onAccept;
	SOCKET serverSocket;
};

using TCP = Windows_TCP;

#endif