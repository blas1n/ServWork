#include "INI.h"
#include <exception>
#include <fstream>

namespace ServWork
{
	INI::INI(const std::string& inPath)
		: map(), path(inPath)
	{
		std::ifstream in{ path };
		if (!in.is_open()) throw std::runtime_error{ "Cannot open config file" };

		char tmp[128];
		std::string buf;

		while (in)
		{
			in.getline(tmp, 128);
			buf = tmp;

			auto idx = buf.find('=');
			map.insert(std::make_pair(buf.substr(0, idx), buf.substr(idx + 1)));
		}

		in.close();
	}

	void INI::Set(const std::string& key, const std::string& value)
	{
		map[key] = value;

		std::ofstream out{ path };
		if (!out.is_open())
			throw std::runtime_error{ "Cannot open config file" };

		for (const auto& pair : map)
			out << pair.first << "=" << pair.second << std::endl;
	}
}