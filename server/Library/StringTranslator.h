#pragma once

#include <cstring>

struct StringTranslator
{
	static void AsciiToUnicode(char* in, wchar_t* out)
	{
		auto len = strlen(in) + 1;
		memset(out, 0, len * 2);

		for (int i = 0; i < len; ++i)
			out[i] = in[i];
	}

	static void UnicodeToAscii(wchar_t* in, char* out)
	{
		auto len = wcslen(in) + 1;
		for (int i = 0; i < len; ++i)
			out[i] = static_cast<char>(in[i]);
	}
};