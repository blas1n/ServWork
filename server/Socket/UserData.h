#pragma once

#include "Def.h"
#include "Receiver.h"
#include "Sender.h"

namespace ServWork
{
	class UserData final
	{
	public:
		UserData();
		~UserData();

		inline const wchar_t* GetIp() const noexcept { return ip; }
		inline void SetIp(const wchar_t* inIp) noexcept { wcsncpy(ip, inIp, 16); }

		inline const Sender* GetSender() const noexcept { return sender; }
		inline const Receiver* GetReceiver() const noexcept { return receiver; }

	protected:
		wchar_t ip[16];
		Sender* sender;
		Receiver* receiver;
	};
}