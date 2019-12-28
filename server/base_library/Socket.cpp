#include "Socket.h"
#include <stdexcept>

namespace ServWork
{
	Socket::Socket(int inLen)
		: s(0), bufLen(inLen) {}

	Socket::Socket(Socket&& other) noexcept
		: s(std::move(other.s)),
		bufLen(std::move(other.bufLen))
	{
		other.s = 0;
	}

	Socket& Socket::operator=(Socket&& other) noexcept
	{
		s = std::move(other.s);
		bufLen = std::move(other.bufLen);
		other.s = 0;
		return *this;
	}

	Socket::~Socket()
	{
		if (s)
			Close();
	}

	void Socket::Open(int port, int queueSize)
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			throw std::runtime_error
			{
				std::string("socket error ") + strerror(errno)
			};
		}

		AddrIn addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);

#if PLATFORM_WINDOWS
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
#elif PLATFORM_LINUX
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif

		int check = bind(s, reinterpret_cast<Addr*>(&addr), sizeof(addr));
		if (check == SOCKET_ERROR)
		{
			throw std::runtime_error
			{
				std::string("bind error ") + strerror(errno)
			};
		}

		check = listen(s, queueSize);
		if (check == SOCKET_ERROR)
		{
			throw std::runtime_error
			{
				std::string("listen error ") + strerror(errno)
			};
		}
	}

	void Socket::Close()
	{
#if PLATFORM_WINDOWS
		closesocket(s);
#elif PLATFORM_LINUX
		close(s);
#endif

		s = 0;
	}

	Socket Socket::Accept(AddrIn& addr, SockLen& len)
	{
		Socket ret{ bufLen };
		ret.s = accept(s, reinterpret_cast<Addr*>(&addr), &len);
		return ret;
	}

	int Socket::Recv(byte* buf)
	{
		return Recv(reinterpret_cast<char*>(buf));
	}

	int Socket::Recv(char* buf)
	{
		return recv(s, reinterpret_cast<char*>(buf), bufLen, 0);
	}

	int Socket::Send(const byte* buf)
	{
		return Send(reinterpret_cast<const char*>(buf));
	}

	int Socket::Send(const char* buf)
	{
		return send(s, reinterpret_cast<const char*>(buf), bufLen, 0);
	}
}