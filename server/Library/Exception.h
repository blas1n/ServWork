#pragma once

#include <exception>
#include <string>

namespace ServWork
{
	namespace Internal
	{
		struct ErrorTag final {};
		struct WarningTag final {};

		template <class Tag>
		class Exception : public std::exception
		{
			using Base = std::exception;

		public:
			explicit Exception(const std::string& msg)
				: Base(msg.c_str()) {}

			explicit Exception(const char* msg)
				: Base(msg) {}
		};
	}

	using Error = Internal::Exception<Internal::ErrorTag>;
	using Warning = Internal::Exception<Internal::WarningTag>;
}