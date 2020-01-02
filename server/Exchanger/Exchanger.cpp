#include "Exchanger.h"

namespace ServWork
{
	void Exchanger::Allocate(size_t size)
	{
		if (maxSize != size)
		{
			if (data) delete[] data;
			data = new char[size];
			maxSize = size;
		}

		curSize = 0;
	}

	void Exchanger::Deallocate() noexcept
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
			maxSize = 0;
		}
	}

	double Exchanger::GetPercent() const
	{
		if (maxSize == 0)
			throw MakeWarning("max_size_is_0");

		return static_cast<double>(curSize) / maxSize;
	}
}