#pragma once

#include "Type.h"

namespace ServWork::EndianTranslator
{
	namespace Internal
	{
		enum class Endianness : ServWork::uint32 {
			LITTLE_ENDIAN = 0x00000001,
			BIG_ENDIAN = 0x01000000,
			UNKNOWN_ENDIAN = 0xFFFFFFFF
		};

		constexpr Endianness GetEndianness() {
			return static_cast<Endianness>(1 & 0xFFFFFFFF);
		}

		template <class T>
		T ReverseEndian(const T& src)
		{
			T dest = src;
			auto ptr = reinterpret_cast<byte*>(&dest);
			std::reverse(ptr, ptr + sizeof(T));
			return dest;
		}
	}

	template <class T>
	T Translate(const T& src)
	{
		if constexpr (Internal::GetEndianness() == Internal::Endianness::BIG_ENDIAN)
			return src;
		return Internal::ReverseEndian(src);
	}
}