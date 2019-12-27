#pragma once

#include <cstddef>
#include <string>

#if PLATFORM_WINDOWS
#	include <WinSock2.h>
	using Addr = SOCKADDR;
	using AddrIn = SOCKADDR_IN;

#	undef SOCKET_ERROR
#	undef INVALID_SOCKET
#elif PLATFORM_LINUX
#	include <sys/socket.h>
	using Addr = struct sockaddr;
	using AddrIn = struct sockaddr_in;
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

	Socket Accept(AddrIn& addr, int& len);

	int Recv(std::byte* buf, int len);
	int Send(const std::byte* buf, int len);

private:
	SOCKET s;
};