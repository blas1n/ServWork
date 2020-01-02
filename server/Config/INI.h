#pragma once

#include "Core.h"
#include <map>

namespace ServWork
{
	class INI final
	{
	public:
		INI(const String& inPath);

		INI(const INI& other) = default;
		INI(INI&& other) = default;

		INI& operator=(const INI& other) = default;
		INI& operator=(INI&& other) = default;

		~INI() = default;

		const String& Get(const String& key) const;
		const String* GetChecked(const String& key) const noexcept;

		void Set(const String& key, const String& value);

		inline const std::map<String, String>& GetAll() const noexcept
		{
			return map;
		}

		inline const String& GetPath() const noexcept
		{
			return path;
		}

	private:
		std::map<String, String> map;
		String path;
	};
}