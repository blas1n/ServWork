#pragma once

#include <map>
#include <string>
#include "INI.h"

namespace ServWork::StringMapper
{
	static inline const std::string& Get(const std::string& key)
	{
		static INI config{ "String.ini" };
		return config.Get(key);
	}
}