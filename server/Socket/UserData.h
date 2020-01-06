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
		
		UserData(const UserData& other);
		UserData(UserData&& other);

		UserData& operator=(const UserData& other);
		UserData& operator=(UserData&& other);
		
		~UserData();

		inline const char_t* GetIp() const noexcept { return ip; }
		inline void SetIp(const char_t* inIp) noexcept { strncpy(ip, inIp, 16); }

		inline const Sender* GetSender() const noexcept { return sender; }
		inline const Receiver* GetReceiver() const noexcept { return receiver; }

	protected:
		char_t ip[16];
		Sender* sender;
		Receiver* receiver;
	};
}