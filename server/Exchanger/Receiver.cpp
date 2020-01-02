#include "Receiver.h"
#include <cstring>

namespace ServWork
{
	size_t Receiver::AddData(char* inData, size_t size)
	{
		memcpy(data + curSize, inData, size);
		curSize += size;
		return curSize;
	}
}