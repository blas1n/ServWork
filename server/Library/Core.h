#pragma once

#include "Exception.h"
#include "Name.h"
#include "StringTranslator.h"
#include "Type.h"

namespace ServWork
{
	inline Warning MakeWarning(const char* msg) noexcept
	{
		return Warning{ Name{ StringTranslator::AsciiToUnicode(msg) } };
	}

	inline Error MakeError(const char* msg) noexcept
	{
		return Error{ Name{ StringTranslator::AsciiToUnicode(msg) } };
	}
}