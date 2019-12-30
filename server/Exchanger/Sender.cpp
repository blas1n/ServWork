#include "Sender.h"

namespace ServWork
{
	size_t Sender::GetLength(char*& outData, size_t size/*= 2048*/)
	{
		outData = data + curSize;

		if (curSize + size < maxSize)
		{
			curSize += size;
			return size;
		}
		
		auto ret = maxSize - curSize;
		curSize = maxSize;
		return ret;
	}
}