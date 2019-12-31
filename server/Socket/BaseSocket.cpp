#include "BaseSocket.h"
#include <chrono>
#include <stdexcept>
#include <thread>
#include "Config.h"
#include "Name.h"

namespace ServWork
{
	BaseSocket::BaseSocket(SockId id/*= INVALID_SOCKET*/)
		: s(id) {}

	BaseSocket::BaseSocket(BaseSocket&& other) noexcept
		: s(std::move(other.s))
	{
		other.s = 0;
	}

	BaseSocket& BaseSocket::operator=(BaseSocket&& other) noexcept
	{
		s = std::move(other.s);
		other.s = 0;
		return *this;
	}

	BaseSocket::~BaseSocket()
	{
		if (s != INVALID_SOCKET)
			Close();
	}

	bool BaseSocket::Send(byte id, Buffer& buf) const
	{
		if (s == INVALID_SOCKET)
			throw std::logic_error{ Name{ "Socket not open" } };

		const auto size = buf.GetCurBufferSize();

		const Header header{ Config::checkKey, id, size };
		buf >>= HEADER_SIZE;
		buf.Set(0, header);

		return recv(s, buf, buf.GetCurBufferSize(), 0) == size;
	}

	bool BaseSocket::Recv(Buffer& buf, size_t size) const
	{
		using namespace std::chrono_literals;
		
		if (s == INVALID_SOCKET)
			throw std::logic_error{ Name{ "Socket not open" } };

		auto tmp = new char[size];
		size_t totalSize = 0;
		uint8 retry = 0;

		while (totalSize < size)
		{
			size_t readSize = recv(s, tmp, size - totalSize, 0);
			buf.Set(totalSize, tmp, readSize);

			if (readSize == SOCKET_ERROR)
			{
				if (++retry > 10) return false;
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
		
		return true;
	}	
}