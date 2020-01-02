#pragma once

#include <WinSock2.h>
#include "Buffer.h"

#undef SOCKET_ERROR
#undef INVALID_SOCKET

namespace ServWork
{
	constexpr uint32 INVALID_SOCKET = ~0;
	constexpr int32 SOCKET_ERROR = -1;

	using Addr = SOCKADDR;
	using AddrIn = SOCKADDR_IN;
	using SockId = SOCKET;
	using SockLen = int;
}