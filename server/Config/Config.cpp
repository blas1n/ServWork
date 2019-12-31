#include "Config.h"
#include "INI.h"

namespace ServWork
{
	void Config::Init()
	{
		static INI config{ PATH };

		port = std::stoi(config.Get("Port"));
		queueSize = std::stoi(config.Get("QueueSize"));
		checkKey = std::stoi(config.Get("CheckKey"));
		maxUser = std::stoi(config.Get("MaxUser"));
		acceptId = std::stoi(config.Get("AcceptId"));
		notifyId = std::stoi(config.Get("NotifyId"));
	}
}