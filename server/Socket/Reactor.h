#pragma once

#include "ServerSocket.h"
#include "UserData.h"

namespace ServWork
{
	class Reactor
	{
	public:
		virtual void OnReceive(const ClientSocket& socket, uint8 id, Buffer buf) {}
		virtual void OnAccept(const ClientSocket& socket) {}
		virtual void OnClose(const ClientSocket& socket) {}
		virtual void OnLimitError(const char_t* ip) {}

		const ServerSocket& GetServer() const noexcept { return *server; }
		void SetServer(const ServerSocket* inServer) noexcept { server = inServer; }

	private:
		const ServerSocket* server;
	};
}