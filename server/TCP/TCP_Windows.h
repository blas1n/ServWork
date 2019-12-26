#if PLATFORM_WINDOWS

#pragma once

#include "Base_TCP.h"
#include <WinSock2.h>

class TCP_Windows final : public Base_TCP
{
public:
	TCP_Windows(int inPort, int inBufSize, int inQueueSize);
	TCP_Windows(const std::string& configPath);

	TCP_Windows(TCP_Windows&& other) noexcept;
	TCP_Windows& operator=(TCP_Windows&& other) noexcept;

	~TCP_Windows() override;

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

using TCP = TCP_Windows;

#endif