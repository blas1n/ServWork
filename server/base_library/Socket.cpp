#include "Socket.h"
#include <stdexcept>

namespace ServWork
{
	Socket::Socket()
		: s(0) {}

	Socket::Socket(Socket&& other) noexcept
		: s(std::move(other.s))
	{
		other.s = 0;
	}

	Socket& Socket::operator=(Socket&& other) noexcept
	{
		s = std::move(other.s);
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
		if (!s) throw std::logic_error{ socketNotOpen };

		Socket ret;
		ret.s = accept(s, reinterpret_cast<Addr*>(&addr), &len);
		return ret;
	}

	int Socket::Recv(Buffer& buf)
	{
		if (!s) throw std::logic_error{ socketNotOpen };
		return recv(s, buf, buf.GetBufferSize(), 0);
	}

	int Socket::Send(const Buffer& buf)
	{
		if (!s) throw std::logic_error{ socketNotOpen };
		return send(s, buf, buf.GetBufferSize(), 0);
	}
}