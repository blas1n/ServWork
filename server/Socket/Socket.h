#pragma once

#include "Buffer.h"
#include "Def.h"

namespace ServWork
{
	class Socket
	{
	public:
		Socket(SockId id = INVALID_SOCKET);

		Socket(const Socket&) = default;
		Socket(Socket&& other) noexcept;

		Socket& operator=(const Socket&) = default;
		Socket& operator=(Socket&& other) noexcept;

		virtual ~Socket();

		virtual void Open() {}
		virtual void Close() noexcept;

		bool Send(byte id, Buffer& buf) const;
		bool Recv(Buffer& buf, size_t size) const;

		inline SockId GetId() const noexcept { return s; }

	protected:
		SockId s;

	private:
		friend bool operator==(const Socket& lhs, const Socket& rhs);
		friend bool operator==(const Socket& lhs, SockId rhs);
	};

	bool operator==(const Socket& lhs, const Socket& rhs)
	{
		return lhs.s == rhs.s;
	}

	bool operator!=(const Socket& lhs, const Socket& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator==(const Socket& lhs, SockId rhs)
	{
		return lhs.s == rhs;
	}

	bool operator!=(const Socket& lhs, SockId rhs)
	{
		return !(lhs == rhs);
	}

	bool operator==(SockId lhs, const Socket& rhs)
	{
		return rhs == lhs;
	}

	bool operator!=(SockId lhs, const Socket& rhs)
	{
		return !(lhs == rhs);
	}
}