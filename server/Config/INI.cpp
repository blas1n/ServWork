#include "INI.h"
#include <fstream>

namespace ServWork
{
	INI::INI(const String& inPath)
		: map(), path(inPath)
	{
		std::wifstream in{ path };
		if (!in.is_open())
			throw MakeError("cannot_open_config_file");

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
	
	const String& INI::Get(const String& key) const
	{
		auto iter = map.find(key);

		if (iter == map.cend())
			throw MakeWarning("cannot_find_key");

		return iter->second;
	}

	const String* INI::GetChecked(const String& key) const noexcept
	{
		auto iter = map.find(key);

		return (iter != map.cend()) ? &(iter->second) : nullptr;
	}

	void INI::Set(const String& key, const String& value)
	{
		map[key] = value;

		std::wofstream out{ path };
		if (!out.is_open())
			throw MakeError("cannot_open_config_file");

		for (const auto& pair : map)
			out << pair.first << STR("=") << pair.second << std::endl;
	}
}