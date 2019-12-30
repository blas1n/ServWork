#pragma once

#include <map>
#include <string>

namespace ServWork
{
	class StringMapper final
	{
	public:
		static void Init();

		static inline const std::string& Get(const std::string& key)
		{
			return mapper[key];
		}

	private:
		constexpr static char* PATH = "String.ini";

		static std::map<std::string, std::string> mapper;
	};
}