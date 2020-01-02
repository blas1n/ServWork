#include "Socket.h"
#include <chrono>
#include <thread>
#include "Config.h"

namespace ServWork
{
	Socket::Socket(SockId id/*= INVALID_SOCKET*/)
		: s(id) {}

	Socket::Socket(Socket&& other) noexcept
		: s(std::exchange(other.s, 0)) {}

	Socket& Socket::operator=(Socket&& other) noexcept
	{
		s = std::exchange(other.s, 0);
		return *this;
	}

	Socket::~Socket()
	{
		if (s != INVALID_SOCKET)
			Close();
	}

	void Socket::Close() noexcept
	{
		closesocket(s);
		s = INVALID_SOCKET;
	}

	void Socket::Send(byte id, Buffer& buf) const
	{
		if (s == INVALID_SOCKET)
			throw MakeWarning("socket_not_open");

		buf >>= HEADER_SIZE;
		
		const auto size = static_cast<uint32>(buf.GetCurSize());
		const Header header{ Config::checkKey, id, size };
		buf.Set(0, header);

		if (send(s, buf, size, 0) != size)
			throw MakeWarning("send_failed");
	}

	void Socket::Recv(Buffer& buf, size_t size) const
	{
		using namespace std::chrono_literals;
		
		if (s == INVALID_SOCKET)
			throw MakeWarning("socket_not_open");

		auto tmp = new char[size];
		size_t totalSize = 0;
		uint8 retry = 0;

		while (totalSize < size)
		{
			size_t readSize = recv(s, tmp, static_cast<int>(size - totalSize), 0);
			buf.Set(totalSize, tmp, readSize);

			if (readSize == SOCKET_ERROR)
			{
				if (++retry > 10)
					throw MakeWarning("recv_failed");
				std::this_thread::sleep_for(50ms);
			}
			else
			{
				retry = 0;
				totalSize += readSize;
				if (totalSize < size)
					std::this_thread::sleep_for(5ms);
			}
		}
	}	
}