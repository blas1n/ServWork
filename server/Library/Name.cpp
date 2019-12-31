#include "ServString.h"
#include "StringMapper.h"

namespace ServWork
{
	String::operator std::string() const
	{
		return StringMapper::Get(id);
	}
}