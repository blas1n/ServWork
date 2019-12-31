#include "UserData.h"
#include "Receiver.h"
#include "Sender.h"

namespace ServWork
{
	UserData::UserData()
		: sock(nullptr),
		sender(new Sender()),
		receiver(new Receiver()),
		ip() {}

	UserData::~UserData()
	{
		delete sender;
		delete receiver;
	}
}