#pragma once

#include <memory>
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

		void Accept();

		inline ClientSocket& FindClient(SockId sock)
		{
			return (*clients)[FindClientIndex(sock)];
		}

		inline const ClientSocket& FindClient(SockId sock) const
		{
			return (*clients)[FindClientIndex(sock)];
		}
		
		size_t FindClientIndex(SockId sock) const;

		inline const auto& GetClients() const noexcept
		{
			return *clients;
		}

		inline long GetEvent() const noexcept override
		{
			return FD_ACCEPT;
		}

	private:
		std::shared_ptr<std::vector<ClientSocket>> clients;
	};
}