#pragma once

#include "INI.h"

namespace ServWork::StringMapper
{
	static const String& Get(const String& key)
	{
		constexpr static char_t PATH[] = STR("String.ini");

		static char_t rootConfigPath[ArrSize(ROOT_PATH) + ArrSize(PATH)];
		static char_t curConfigPath[ArrSize(CUR_PATH) + ArrSize(PATH)];

		static INI rootConfig{ strcat(strcat(rootConfigPath, ROOT_PATH), PATH) };
		static INI curConfig{ strcat(strcat(curConfigPath, CUR_PATH), PATH) };

		const auto root = rootConfig.Get(key);
		if (root)
			return *root;

		const auto cur = curConfig.Get(key);
		if (cur)
			return *cur;

		return key;
	}
}