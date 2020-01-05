#include "Name.h"
#include "StringMapper.h"

namespace ServWork
{
	String Name::Get() const
	{
		return StringMapper::Get(id);
	}
}