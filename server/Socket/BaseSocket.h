#pragma once

#include "Def.h"
#include <type_traits>

namespace ServWork
{
	class BaseSocket
	{
	public:
		BaseSocket(SockId id = INVALID_SOCKET);

		BaseSocket(const BaseSocket&) = default;
		BaseSocket(BaseSocket&& other) noexcept;

		BaseSocket& operator=(const BaseSocket&) = default;
		BaseSocket& operator=(BaseSocket&& other) noexcept;

		virtual ~BaseSocket();

		virtual void Open() {}
		virtual void Close() {}

		bool Send(byte id, Buffer& buf) const;
		bool Recv(Buffer& buf, size_t size) const;

		virtual inline long GetDefaultEvent() const noexcept
		{
			return FD_CLOSE;
		}

	protected:
		SockId s;

	private:
		friend bool operator==(const BaseSocket& lhs, const BaseSocket& rhs);
		friend bool operator==(const BaseSocket& lhs, SockId rhs);
		friend bool operator==(SockId lhs, const BaseSocket& rhs);
	};

	bool operator==(const BaseSocket& lhs, const BaseSocket& rhs)
	{
		return lhs.s == rhs.s;
	}

	bool operator!=(const BaseSocket& lhs, const BaseSocket& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator==(const BaseSocket& lhs, SockId rhs)
	{
		return lhs.s == rhs;
	}

	bool operator!=(const BaseSocket& lhs, SockId rhs)
	{
		return !(lhs == rhs);
	}

	bool operator==(SockId lhs, const BaseSocket& rhs)
	{
		return lhs == rhs.s;
	}

	bool operator!=(SockId lhs, const BaseSocket& rhs)
	{
		return !(lhs == rhs);
	}
}