#pragma once

#include "Def.h"
#include "BaseSocket.h"
#include "Receiver.h"
#include "Sender.h"

namespace ServWork
{
	class UserData
	{
	public:
		UserData();
		~UserData();

		inline const SockId GetSocket() const noexcept { return sock; }
		inline void SetSocket(const SockId inSock) noexcept { sock = inSock; }

		inline const Sender* GetSender() const noexcept { return sender; }
		inline const Receiver* GetReceiver() const noexcept { return receiver; }

		inline const wchar_t* GetIp() const noexcept { return ip; }
		inline void SetIp(const wchar_t* inIp) noexcept { wcsncpy(ip, inIp, 16); }

		virtual inline UserData* Clone() const noexcept { return new UserData(); }

	protected:
		SockId sock;
		Sender* sender;
		Receiver* receiver;
		wchar_t ip[16];
	};
}