#pragma once

#include "EventSocket.h"
#include "UserData.h"

namespace ServWork
{
	class ClientSocket final : public EventSocket
	{
		using Base = EventSocket;

	public:
		ClientSocket()
			: Base(), data(new UserData{ }) {}

		~ClientSocket() override
		{
			delete data;
		}

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
		UserData* data;
	};
}