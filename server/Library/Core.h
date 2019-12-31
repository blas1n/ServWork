#pragma once

#include <cstddef>
#include <stdexcept>

namespace ServWork
{
	using LogicError = std::logic_error;
	using RuntimeError = std::runtime_error;

	using byte = unsigned char;

	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;

	using int8 = signed char;
	using int16 = signed short;
	using int32 = signed int;
	using int64 = signed long long;
	
#pragma pack(push, 1)
	extern "C" struct Header
	{
		uint8 check;
		uint8 id;
		uint32 size;
	};
#pragma pack(pop)

	constexpr auto HEADER_SIZE = sizeof(Header);
}