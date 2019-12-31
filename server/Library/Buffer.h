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

		Buffer(size_t bufferSize);

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
			if (index >= curBufferSize)
				throw std::logic_error{ "Index out of bound." };

			return buffer[index];
		}

		inline Buffer& operator+=(const char* content)
		{
			Set(curBufferSize, content);
			return *this;
		}

		template <size_t N>
		inline Buffer& operator+=(const byte(&content)[N])
		{
			Set(curBufferSize, content);
			return *this;
		}

		template <class T>
		inline Buffer& operator+=(const T& value)
		{
			Set(curBufferSize, value);
			return *this
		}

		Buffer& operator<<=(size_t index) noexcept;
		Buffer& operator>>=(size_t index) noexcept;

		inline void Init() noexcept
		{
			curBufferSize = 0;
			memset(*this, 0, maxBufferSize);
		}

		inline char* Get(size_t index)
		{
			if (index >= curBufferSize)
				throw std::logic_error{ "Index out of bound." };

			return static_cast<char*>(*this) + index;
		}

		inline const char* Get(size_t index) const
		{
			if (index >= curBufferSize)
				throw std::logic_error{ "Index out of bound." };

			return static_cast<const char*>(*this) + index;
		}

		void Set(size_t index, const char* content);
		void Set(size_t index, const char* content, size_t size);

		template <size_t N>
		inline void Set(size_t index, const byte(&content)[N])
		{
			Set(index, reinterpret_cast<const char*>(content), N);
		}

		inline void Set(size_t index, const byte* content, size_t size)
		{
			Set(index, reinterpret_cast<const char*>(content), size);
		}

		template <class T>
		inline void Set(size_t index, const T& value)
		{
			Set(index, reinterpret_cast<const byte*>(&value), sizeof(T));
		}

		inline size_t GetCurBufferSize() const noexcept
		{
			return curBufferSize;
		}

		inline size_t GetMaxBufferSize() const noexcept
		{
			return maxBufferSize;
		}

		inline operator byte*() noexcept
		{
			return buffer;
		}

		inline operator const byte*() const noexcept
		{
			return buffer;
		}

		inline operator char*() noexcept
		{
			return reinterpret_cast<char*>(buffer);
		}

		inline operator const char*() const noexcept
		{
			return reinterpret_cast<const char*>(buffer);
		}

		inline operator void*() noexcept
		{
			return reinterpret_cast<void*>(buffer);
		}

		inline operator const void*() const noexcept
		{
			return reinterpret_cast<const void*>(buffer);
		}

		inline operator bool() const noexcept
		{
			return buffer;
		}

	private:
		byte* buffer;
		size_t curBufferSize;
		size_t maxBufferSize;
	};
}