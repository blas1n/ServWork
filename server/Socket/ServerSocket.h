#pragma once

#include "ReactableSocket.h"

namespace ServWork
{
	class ServerSocket final : public ReactableSocket
	{
	public:
		ServerSocket(class UserData* proto);
		~ServerSocket() override;

		void Open() override;
		void Close() override;

		int OnAccept(WPARAM wParam, LPARAM lParam);
		void OnEvent(WPARAM wParam, LPARAM lParam);

		int FindUserIndex(SockId sock);
		UserData* FindUserData(SockId sock);

		inline long GetDefaultEvent() const noexcept override
		{
			return BaseSocket::GetDefaultEvent() | FD_ACCEPT;
		}

		inline UserData** GetUsers() noexcept { return users; }
		inline const UserData** GetUsers() const noexcept { return users; }

	private:
		UserData** users;
	};
}