#include "StringMapper.h"
#include "INI.h"

namespace ServWork
{
	void StringMapper::Init()
	{
		static INI config{ PATH };
		mapper = config.GetAll();
	}
}