#include "UserData.h"

namespace ServWork
{
	UserData::UserData()
		: ip(),
		sender(new Sender()),
		receiver(new Receiver()) {}

	UserData::~UserData()
	{
		delete sender;
		delete receiver;
	}
}