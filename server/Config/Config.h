#pragma once

#include "Core.h"

namespace ServWork
{
	struct Config final
	{
		static void Init();

		static int32 port;
		static int32 queueSize;

		static uint8 checkKey;
		static uint32 maxUser;

		static int32 acceptId;
		static int32 notifyId;

	private:
		constexpr static char_t PATH[] = STR("Config.ini");
	};
}