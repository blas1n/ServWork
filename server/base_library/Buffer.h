#pragma once

namespace ServWork
{
	using byte = unsigned char;

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
			return reinterpret_cast<char*>(buffer);
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