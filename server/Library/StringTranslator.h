#pragma once

#include <string>

namespace ServWork::StringTranslator
{
	inline std::wstring AsciiToUnicode(const std::string& in)
	{
		return std::wstring(in.begin(), in.end());
	}

	inline std::string UnicodeToAscii(const std::wstring& in)
	{
		return std::string(in.begin(), in.end());
	}
}