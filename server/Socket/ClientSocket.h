#pragma once

#include "EventSocket.h"

namespace ServWork
{
	class ClientSocket final : public EventSocket
	{
		using Base = EventSocket;

	public:
		ClientSocket(wchar_t* ip);
		~ClientSocket() override;

		inline long GetEvent() const noexcept override
		{
			return FD_READ | FD_CLOSE;
		}

		inline class UserData& GetData() noexcept { return *data; }
		inline const UserData& GetData() const noexcept { return *data; }

	private:
		UserData* data;
	};
}