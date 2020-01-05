#pragma once

#pragma warning(disable:4996)

#include <cstddef>
#include <string>

using namespace std::string_literals;

#define _STR(x) L##x
#define STR(x) _STR(x)

namespace ServWork
{
	using byte = unsigned char;

	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;

	using int8 = signed char;
	using int16 = signed short;
	using int32 = signed int;
	using int64 = signed long long;
	
	using char_t = wchar_t;
	using String = std::wstring;

#pragma pack(push, 1)
	extern "C" struct Header
	{
		uint8 check;
		uint8 id;
		uint32 size;
	};
#pragma pack(pop)

	constexpr char_t ROOT_PATH[] = STR("");
	constexpr char_t CUR_PATH[] = STR("");
	constexpr auto HEADER_SIZE = sizeof(Header);

	template <typename T, size_t N>
	constexpr size_t ArrSize(T(&)[N]) noexcept { return N; }
}

#undef ROOT_DIR
#undef CUR_DIR