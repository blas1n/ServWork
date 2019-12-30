#pragma once

#include "Core.h"
#include <cstring>
#include <stdexcept>

namespace ServWork
{
	class Buffer final
	{
	public:
		Buffer() = default;
		Buffer(std::nullptr_t) : Buffer() {}

		Buffer(size_t inBufferSize);
		
		Buffer(const Buffer& other);
		Buffer(Buffer&& other) noexcept;

		Buffer& operator=(const Buffer& other);
		Buffer& operator=(Buffer&& other) noexcept;

		~Buffer();

		Buffer& operator=(const char* content)
		{
			Init();
			Set(0, content);
			return *this;
		}

		Buffer& operator=(const byte* content)
		{
			Init();
			Set(0, content);
			return *this;
		}

		byte operator[](size_t index) const
		{
			if (index >= bufferSize)
				throw std::logic_error{ "Index out of bound." };

			return buffer[index];
		}

		inline void Init() noexcept
		{
			memset(*this, 0, bufferSize);
		}

		inline char* Get(size_t index)
		{
			return static_cast<char*>(*this) + index;
		}

		inline const char* Get(size_t index) const
		{
			return static_cast<const char*>(*this) + index;
		}

		inline void Set(size_t index, const char* content)
		{
			strncpy(Get(index), content,
				strnlen(content, bufferSize - index));
		}

		inline void Set(size_t index, const byte* content)
		{
			Set(index, reinterpret_cast<const char*>(content));
		}

		inline size_t GetBufferSize() const
		{
			return bufferSize;
		}

		inline operator byte*()
		{
			return buffer;
		}

		inline operator const byte*() const
		{
			return buffer;
		}

		inline operator char*()
		{
			return reinterpret_cast<char*>(buffer);
		}

		inline operator const char*() const
		{
			return reinterpret_cast<const char*>(buffer);
		}

		inline operator void*()
		{
			return reinterpret_cast<void*>(buffer);
		}

		inline operator const void*() const
		{
			return reinterpret_cast<const void*>(buffer);
		}

		inline operator bool() const
		{
			return buffer;
		}

	private:
		byte* buffer;
		size_t bufferSize;
	};
}