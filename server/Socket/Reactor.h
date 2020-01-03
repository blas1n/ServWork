#pragma once

#include "ServerSocket.h"
#include "UserData.h"

namespace ServWork
{
	class Reactor
	{
	public:
		virtual void OnReceive(const EventSocket& socket, uint8 id, Buffer buf) {}
		virtual void OnAccept(const EventSocket& socket) {}
		virtual void OnClose(const EventSocket& socket) {}
		virtual void OnLimitError(const char_t* ip) {}

		const ServerSocket& GetServer() const noexcept { return *server; }
		void SetServer(const ServerSocket* inServer) noexcept { server = inServer; }

	private:
		const ServerSocket* server;
	};
}