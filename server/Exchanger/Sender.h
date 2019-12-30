#pragma once

#include "Exchanger.h"

namespace ServWork
{
	class Sender final : public Exchanger
	{
	public:
		size_t GetLength(char*& outData, size_t size = 2048);

		inline bool IsProcess() const noexcept
		{
			return curSize < maxSize;
		}
	};
}