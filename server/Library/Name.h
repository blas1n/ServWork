#pragma once

#include <string>
#include <utility>

namespace ServWork
{
	class Name final
	{
	public:
		Name() noexcept : id() {}

		Name(const std::string& inId) : id(inId) {}
		Name(std::string&& inId) : id(std::move(inId)) {}

		Name(const Name&) = default;
		Name(Name&&) = default;

		Name(const std::string& inId) { id = inId; }
		Name(std::string&& inId) { id = std::move(inId); }

		Name& operator=(const Name&) = default;
		Name& operator=(Name&&) = default;

		~Name() = default;

		operator std::string() const;

	private:
		std::string id;
	};
}