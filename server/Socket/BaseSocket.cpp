#include "BaseSocket.h"
#include <chrono>
#include <stdexcept>
#include <thread>
#include "Config.h"
#include "Name.h"
#include "Reactor.h"

namespace ServWork
{
	BaseSocket::BaseSocket(SockId id/*= INVALID_SOCKET*/)
		: s(id),
		handle(nullptr) {}

	BaseSocket::BaseSocket(BaseSocket&& other) noexcept
		: s(std::move(other.s)),
		handle(std::move(other.handle)),
		reactor(std::move(other.reactor))
	{
		other.s = 0;
	}

	BaseSocket& BaseSocket::operator=(BaseSocket&& other) noexcept
	{
		s = std::move(other.s);
		handle = std::move(other.handle);
		reactor = std::move(other.reactor);
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

	void BaseSocket::ProcessRecvEvent()
	{
		::WSAAsyncSelect(s, handle, Config::notifyId, GetDefaultEvent());

		uint8 key = 0;
		recv(s, reinterpret_cast<char*>(&key), 1, 0);

		if (key == Config::checkKey)
		{
			Close();
			return;
		}

		uint8 id = 0;
		recv(s, reinterpret_cast<char*>(&id), 1, 0);

		uint32 size = 0;
		recv(s, reinterpret_cast<char*>(&size), sizeof(uint32), 0);

		Buffer buf{ size };

		if (size > 0)
		{
			if (!Recv(buf, size))
			{
				Close();
				return;
			}
		}

		reactor->OnReceive(*this, id, std::move(buf));
		::WSAAsyncSelect(s, handle, Config::notifyId, GetDefaultEvent() | FD_READ);
	}
}