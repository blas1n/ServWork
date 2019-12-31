#pragma once

#include "BaseSocket.h"

namespace ServWork
{
	class Reactor
	{
	public:
		virtual void OnReceive(const BaseSocket& socket, uint8 id, Buffer buf) = 0;
	};
}