#include "UserData.h"
#include "Receiver.h"
#include "Sender.h"

namespace ServWork
{
	UserData::UserData()
		: sock(0),
		sender(new Sender()),
		receiver(new Receiver()),
		ip() {}

	UserData::~UserData()
	{
		delete sender;
		delete receiver;
	}
}