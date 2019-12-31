#pragma once

#include "Def.h"
#include <type_traits>

namespace ServWork
{
	class BaseSocket
	{
	public:
		BaseSocket();

		BaseSocket(const BaseSocket&) = default;
		BaseSocket(BaseSocket&& other) noexcept;

		BaseSocket& operator=(const BaseSocket&) = default;
		BaseSocket& operator=(BaseSocket&& other) noexcept;

		virtual ~BaseSocket();

		virtual void Open() = 0;
		virtual void Close() = 0;

		bool Send(byte id, Buffer& buf) const;
		bool Recv(Buffer& buf, size_t size) const;

		template <class Reactor>
		void ProcessRecvEvent();

		inline void SetHandle(HWND inHandle) noexcept { handle = inHandle; }
		
		virtual inline long GetDefaultEvent() const noexcept
		{
			return FD_CLOSE;
		}

	protected:
		SockId s;

	private:
		HWND handle;
	};

	template <class Reactor>
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
			if (!Recv(buf))
			{
				Close();
				return;
			}
		}

		if (Reactor::OnReceive(*this, id, buf))
		{
			::WSAAsyncSelect(s, handle, Config::notifyId, GetDefaultEvent() | FD_READ);
		}
	}
}