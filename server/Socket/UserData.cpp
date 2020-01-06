#include "UserData.h"

namespace ServWork
{
	UserData::UserData()
		: ip(),
		sender(new Sender()),
		receiver(new Receiver()) {}

	UserData::UserData(const UserData& other)
		: ip(),
		sender(new Sender{ }),
		receiver(new Receiver{ })
	{
		SetIp(other.ip);
	}

	UserData::UserData(UserData&& other)
		: ip(),
		sender(std::exchange(other.sender, nullptr)),
		receiver(std::exchange(other.receiver, nullptr))
	{
		SetIp(other.ip);
	}

	UserData& UserData::operator=(const UserData& other)
	{
		SetIp(other.ip);
		sender = new Sender{ };
		receiver = new Receiver{ };
		return *this;
	}

	UserData& UserData::operator=(UserData&& other)
	{
		SetIp(other.ip);
		sender = std::exchange(other.sender, nullptr);
		receiver = std::exchange(other.receiver, nullptr);
		return *this;
	}

	UserData::~UserData()
	{
		if (sender)
			delete sender;

		if (receiver)
			delete receiver;
	}
}