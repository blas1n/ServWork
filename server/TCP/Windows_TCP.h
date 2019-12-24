#if PLATFORM_WINDOWS

#pragma once

#include "Base_TCP.h"
#include <WinSock2.h>

class Windows_TCP : public Base_TCP
{
public:
	Windows_TCP();
	~Windows_TCP();

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

private:
	std::function<void(SOCKET, char*)> onAccept;
	SOCKET serverSocket;
};

using TCP = Windows_TCP;

#endif