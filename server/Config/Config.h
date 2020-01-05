#pragma once

#include "Type.h"

namespace ServWork
{
	class Config final
	{
	public:
		static void Init();

		inline static int32 port = 0;
		inline static int32 queueSize = 0;

		inline static uint8 checkKey = 0;
		inline static uint32 maxUser = 0;

	private:
		constexpr static char_t PATH[] = STR("Config.ini");
	};
}