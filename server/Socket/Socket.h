#pragma once

#include "Buffer.h"
#include "Def.h"

namespace ServWork
{
	namespace Internal
	{
		enum class Endianness : uint32 {
			LITTLE_ENDIAN = 0x00000001,
			BIG_ENDIAN = 0x01000000,
			UNKNOWN_ENDIAN = 0xFFFFFFFF
		};

		constexpr Endianness GetEndianness() {
			return static_cast<Endianness>(1 & 0xFFFFFFFF);
		}

		template <class T>
		T ReverseEndian(const T& src)
		{
			T dest = src;
			auto ptr = reinterpret_cast<byte*>(&dest);
			std::reverse(ptr, ptr + sizeof(T));
			return dest;
		}

		template <class T>
		T SwapData(const T& src)
		{
			if constexpr (GetEndianness() == Endianness::BIG_ENDIAN)
				return src;
			return ReverseEndian(src);
		}
	}

	class Socket
	{
	public:
		Socket();

		Socket(const Socket&) = default;
		Socket(Socket&& other) noexcept;

		Socket& operator=(const Socket&) = default;
		Socket& operator=(Socket&& other) noexcept;

		virtual ~Socket();

		virtual void Open() {}
		virtual void Close() noexcept;

		void Send(byte id, const Buffer& buf) const;
		void Recv(Buffer& buf, size_t size) const;

		inline SockId GetId() const noexcept { return s; }
		inline SockId SetId(SockId id) noexcept { return s = id; }

	protected:
		SockId s;

	private:
		friend bool operator==(const Socket& lhs, const Socket& rhs);
		friend bool operator==(const Socket& lhs, SockId rhs);
	};

	inline bool operator==(const Socket& lhs, const Socket& rhs)
	{
		return lhs.s == rhs.s;
	}

	inline bool operator!=(const Socket& lhs, const Socket& rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator==(const Socket& lhs, SockId rhs)
	{
		return lhs.s == rhs;
	}

	inline bool operator!=(const Socket& lhs, SockId rhs)
	{
		return !(lhs == rhs);
	}

	inline bool operator==(SockId lhs, const Socket& rhs)
	{
		return rhs == lhs;
	}

	inline bool operator!=(SockId lhs, const Socket& rhs)
	{
		return !(lhs == rhs);
	}
}