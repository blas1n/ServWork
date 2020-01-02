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

		Name& operator=(const std::string& inId) { id = inId; }
		Name& operator=(std::string&& inId) { id = std::move(inId); }

		Name& operator=(const Name&) = default;
		Name& operator=(Name&&) = default;

		~Name() = default;

		inline operator std::string() const
		{
			return Get();
		}

		std::string Get() const;

	private:
		std::string id;
	};
}