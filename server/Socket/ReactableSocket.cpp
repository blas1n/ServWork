#include "ReactableSocket.h"
#include "Config.h"
#include "Name.h"

namespace ServWork
{
	ReactableSocket::ReactableSocket(SockId id/*= INVALID_SOCKET*/)
		: BaseSocket(id), handle(nullptr), reactor(nullptr) {}

	void ReactableSocket::ProcessRecvEvent()
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