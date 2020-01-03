#pragma once

#include "ServerSocket.h"
#include "UserData.h"

namespace ServWork
{
	class Reactor
	{
	public:
		Reactor(const ServerSocket& inServer)
			: server(inServer) {}

		virtual void OnReceive(const ClientSocket& socket, uint8 id, Buffer buf) {}
		virtual void OnAccept(const ClientSocket& socket) {}
		virtual void OnClose(const ClientSocket& socket) {}
		virtual void OnLimitError(const char_t* ip) {}

		const ServerSocket& GetServer() const noexcept { return server; }

	private:
		const ServerSocket& server;
	};
}