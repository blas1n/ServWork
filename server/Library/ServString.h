#pragma once

#include <string>
#include <utility>

namespace ServWork
{
	class String final
	{
	public:
		String(const std::string& inId) : id(inId) {}
		String(std::string&& inId) : id(std::move(inId)) {}

		String(const String&) = default;
		String(String&&) = default;

		String(const std::string& inId) { id = inId; }
		String(std::string&& inId) { id = std::move(inId); }

		String& operator=(const String&) = default;
		String& operator=(String&&) = default;

		~String() = default;

		operator std::string() const;

	private:
		std::string id;
	};
}