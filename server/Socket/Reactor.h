#pragma once

#include "BaseSocket.h"
#include "UserData.h"

namespace ServWork
{
	class Reactor
	{
	public:
		virtual void OnReceive(const BaseSocket& socket, uint8 id, Buffer buf) {}
		virtual void OnAccept(UserData* user) {}
		virtual void OnClose(UserData* user) {}
		virtual void OnLimitError(const wchar_t* ip) {}
	};
}