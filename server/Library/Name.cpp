#include "Name.h"
#include "StringMapper.h"

namespace ServWork
{
	std::string Name::Get() const
	{
		return StringMapper::Get(id);
	}
}