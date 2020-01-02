#pragma once

#include "Exchanger.h"

namespace ServWork
{
	class Receiver final : public Exchanger
	{
	public:
		size_t AddData(char* inData, size_t size);
		
		inline char* GetData() noexcept
		{
			return data;
		}

		inline const char* GetData() const noexcept
		{
			return data;
		}
	};
}