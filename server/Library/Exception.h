#pragma once

#include "Name.h"
#include "StringTranslator.h"
#include "Type.h"

#define CREATE_EXCEPTION(name) \
namespace ServWork \
{ \
	namespace Internal { struct name##Tag final {}; } \
	using name = Internal::ExceptionTemplate<Internal::name##Tag>; \
	inline name Make##name(const char* msg) noexcept \
	{ \
		return name{ Name{ StringTranslator::AsciiToUnicode(msg) } }; \
	} \
}

namespace ServWork
{
	class Exception
	{
	public:
		explicit Exception(const String& inMsg)
			: msg(inMsg) {}

		explicit Exception(const char_t* inMsg)
			: msg(inMsg) {}

		Exception(const Exception&) noexcept = default;
		Exception(Exception&&) noexcept = default;

		Exception& operator=(const Exception&) noexcept = default;
		Exception& operator=(Exception&&) noexcept = default;

		virtual ~Exception() = default;

		const char_t* What() const noexcept
		{
			return msg.data();
		}

	private:
		String msg;
	};

	namespace Internal
	{
		template <class Tag>
		class ExceptionTemplate final : public Exception
		{
			using Base = Exception;

		public:
			explicit ExceptionTemplate(const String& inMsg)
				: Base(inMsg) {}

			explicit ExceptionTemplate(const char_t* inMsg)
				: Base(inMsg) {}
		};
	}
}

CREATE_EXCEPTION(Error)
CREATE_EXCEPTION(Warning)