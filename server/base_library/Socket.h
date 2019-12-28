#pragma once

#include <cstddef>
#include <string>

#if PLATFORM_WINDOWS
#	include <WinSock2.h>

namespace ServWork
{
	using Addr = SOCKADDR;
	using AddrIn = SOCKADDR_IN;
	using SockId = SOCKET;
	using SockLen = int;
}

#	undef SOCKET_ERROR
#	undef INVALID_SOCKET
#elif PLATFORM_LINUX
#	include <arpa/inet.h>
#	include <cstring>
#	include <fcntl.h>
#	include <errno.h>
#	include <sys/socket.h>
#	include <sys/stat.h>
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <unistd.h>

namespace ServWork
{
	using Addr = struct sockaddr;
	using AddrIn = struct sockaddr_in;
	using SockId = int;
	using SockLen = socklen_t;
}
#endif

namespace ServWork
{
	constexpr auto INVALID_SOCKET = ~0;
	constexpr auto SOCKET_ERROR = -1;

	using byte = unsigned char;

	class Socket final
	{
	public:
		Socket(int inLen);

		Socket(const Socket& other) = default;
		Socket(Socket&& other) noexcept;

		Socket& operator=(const Socket& other) = default;
		Socket& operator=(Socket&& other) noexcept;

		~Socket();

		void Open(int port, int queueSize);
		void Close();

		Socket Accept(AddrIn& addr, SockLen& len);

		int Recv(byte* buf);
		int Send(const byte* buf);

	private:
		SockId s;
		int bufLen;
	};
}