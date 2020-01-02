#include "EventSocket.h"
#include "Config.h"
#include "EventManager.h"
#include "Reactor.h"

namespace ServWork
{
	EventSocket::EventSocket(SockId id/*= INVALID_SOCKET*/)
		: Base(id), reactor(nullptr) {}

	void EventSocket::Open()
	{
		EventManager::Get().RegisterEvent(*this, GetEvent());
	}

	void EventSocket::Close() noexcept
	{
		EventManager::Get().UnregisterEvent(*this);
		Base::Close();
	}

	void EventSocket::OnAccept()
	{
		reactor->OnAccept(*this);
	}

	void EventSocket::OnReceive()
	{
		ProcessRecvEvent();
	}

	void EventSocket::OnClose()
	{
		reactor->OnClose(*this);
	}

	void EventSocket::ProcessRecvEvent()
	{
		EventManager::Get().ChangeEvent(*this, GetEvent() | ~FD_READ);

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
		if (size > 0) Recv(buf, size);

		reactor->OnReceive(*this, id, std::move(buf));
		EventManager::Get().ChangeEvent(*this, GetEvent());
	}	
}