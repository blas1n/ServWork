#include "EventSocket.h"
#include "EventManager.h"

namespace ServWork
{
	EventSocket::EventSocket()
		: Base(), reactor(nullptr) {}

	void EventSocket::Open()
	{
		EventManager::Get().RegisterEvent(*this, GetEvent());
	}

	void EventSocket::Close() noexcept
	{
		EventManager::Get().UnregisterEvent(*this);
		Base::Close();
	}
}