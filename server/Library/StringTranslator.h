#pragma once

#include <string>

struct StringTranslator
{
	static inline std::wstring AsciiToUnicode(const std::string& in)
	{
		return std::wstring(in.begin(), in.end());
	}

	static inline std::string UnicodeToAscii(const std::wstring& in)
	{
		return std::string(in.begin(), in.end());
	}
};