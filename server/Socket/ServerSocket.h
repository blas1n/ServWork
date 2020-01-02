#pragma once

#include "EventSocket.h"
#include <vector>
#include "ClientSocket.h"

namespace ServWork
{
	class ServerSocket final : public EventSocket
	{
		using Base = EventSocket;

	public:
		ServerSocket();

		ServerSocket(const ServerSocket&) = default;
		ServerSocket(ServerSocket&&) = default;

		ServerSocket& operator=(const ServerSocket&) = default;
		ServerSocket& operator=(ServerSocket&&) = default;

		~ServerSocket() override = default;

		void Open() override;
		void Close() noexcept override;

		void OnAccept() override;

		inline ClientSocket& FindClient(SockId sock)
		{
			return clients[FindClientIndex(sock)];
		}

		inline const ClientSocket& FindClient(SockId sock) const
		{
			return clients[FindClientIndex(sock)];
		}
		
		size_t FindClientIndex(SockId sock) const;

		inline long GetEvent() const noexcept override
		{
			return FD_ACCEPT;
		}

	private:
		std::vector<ClientSocket> clients;
		size_t clientNum;
	};
}