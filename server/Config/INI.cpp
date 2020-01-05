#include "INI.h"
#include <fstream>
#include <iostream>

namespace ServWork
{
	INI::INI(const String& inPath)
		: map(), path(inPath)
	{
		std::wifstream in{ path };
		if (!in.is_open())
		{
			std::cout << "Cannot open config file" << std::endl;
			exit(1);
		}

		char_t tmp[128];
		String buf;

		while (in)
		{
			in.getline(tmp, 128);
			buf = tmp;

			auto idx = buf.find(STR('='));
			map.insert(std::make_pair(buf.substr(0, idx), buf.substr(idx + 1)));
		}

		in.close();
	}

	const String* INI::Get(const String& key) const noexcept
	{
		auto iter = map.find(key);
		return (iter != map.cend()) ? &(iter->second) : nullptr;
	}

	void INI::Set(const String& key, const String& value)
	{
		map[key] = value;
		std::wofstream out{ path };
		for (const auto& pair : map)
			out << pair.first << STR("=") << pair.second << std::endl;
	}
}