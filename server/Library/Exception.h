#pragma once

#include "Type.h"

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
		struct ErrorTag final {};
		struct WarningTag final {};

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

	using Error = Internal::ExceptionTemplate<Internal::ErrorTag>;
	using Warning = Internal::ExceptionTemplate<Internal::WarningTag>;
}