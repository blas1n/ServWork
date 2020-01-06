#pragma once

#include "EventSocket.h"
#include <memory>
#include "UserData.h"

namespace ServWork
{
	class ClientSocket final : public EventSocket
	{
		using Base = EventSocket;

	public:
		ClientSocket()
			: Base(), data(std::make_shared<UserData>()) {}

		ClientSocket(const ClientSocket&) = default;
		ClientSocket(ClientSocket&&) = default;

		ClientSocket& operator=(const ClientSocket&) = default;
		ClientSocket& operator=(ClientSocket&&) = default;

		~ClientSocket() override = default;

		void OnAccept();
		void OnReceive();
		void OnClose();

		inline long GetEvent() const noexcept override
		{
			return FD_READ | FD_CLOSE;
		}

		inline UserData& GetData() noexcept { return *data; }
		inline const UserData& GetData() const noexcept { return *data; }

	private:
		std::shared_ptr<UserData> data;
	};
}