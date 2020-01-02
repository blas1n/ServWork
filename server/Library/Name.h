#pragma once

#include "Type.h"
#include <utility>

namespace ServWork
{
	class Name final
	{
	public:
		Name() noexcept : id() {}

		Name(const String& inId) : id(inId) {}
		Name(String&& inId) : id(std::move(inId)) {}

		Name(const Name&) = default;
		Name(Name&&) = default;

		Name& operator=(const String& inId) { id = inId; }
		Name& operator=(String&& inId) { id = std::move(inId); }

		Name& operator=(const Name&) = default;
		Name& operator=(Name&&) = default;

		~Name() = default;

		inline operator String() const
		{
			return Get();
		}

		String Get() const;

	private:
		String id;
	};
}