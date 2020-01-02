#include "Config.h"
#include "INI.h"

namespace ServWork
{
	void Config::Init()
	{
		static char_t ABS_PATH[ArrSize(ROOT_PATH) + ArrSize(PATH)];
		static INI config{ wcscat(wcscat(ABS_PATH, ROOT_PATH), PATH) };

		port =		std::stoi(config.Get(STR("Port")));
		queueSize = std::stoi(config.Get(STR("QueueSize")));
		checkKey =	std::stoi(config.Get(STR("CheckKey")));
		maxUser =	std::stoi(config.Get(STR("MaxUser")));
	}
}