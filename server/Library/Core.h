#pragma once

#include "Exception.h"
#include "Name.h"
#include "StringTranslator.h"
#include "Type.h"

namespace ServWork
{
	Warning MakeWarning(const char* msg)
	{
		std::string str(msg);
		auto wStr = StringTranslator::AsciiToUnicode(str);
		return Warning{ Name{ wStr } };
	}

	Error MakeError(const char* msg)
	{
		std::string str(msg);
		auto wStr = StringTranslator::AsciiToUnicode(str);
		return Error{ Name{ wStr } };
	}
}