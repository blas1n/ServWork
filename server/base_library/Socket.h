#pragma once

#include <cstddef>
#include <string>

#if PLATFORM_WINDOWS
#	include <WinSock2.h>
	using Addr = SOCKADDR;
	using AddrIn = SOCKADDR_IN;
	using SockId = SOCKET;
	using SockLen = int;

#	undef SOCKET_ERROR
#	undef INVALID_SOCKET
#elif PLATFORM_LINUX
#	include <sys/socket.h>
	using Addr = struct sockaddr;
	using AddrIn = struct sockaddr_in;
	using SockId = int;
	using SockLen = socklen_t;
#endif

constexpr auto INVALID_SOCKET = ~0;
constexpr auto SOCKET_ERROR = -1;

class Socket final
{
public:
	Socket();

	Socket(const Socket& other) = default;
	Socket(Socket&& other) noexcept;

	Socket& operator=(const Socket& other) = default;
	Socket& operator=(Socket&& other) noexcept;

	~Socket();

	void Open(int port, int queueSize);
	void Close();

	Socket Accept(AddrIn& addr, SockLen& len);

	int Recv(std::byte* buf, int len);
	int Send(const std::byte* buf, int len);

private:
	SockId s;
};