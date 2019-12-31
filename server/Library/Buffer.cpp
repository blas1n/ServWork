#include "Buffer.h"
#include <utility>
#include "Name.h"

namespace ServWork
{
	Buffer::Buffer(size_t bufferSize)
		: buffer(nullptr),
		curBufferSize(0),
		maxBufferSize(bufferSize)
	{
		if (buffer > 0)
			buffer = new byte[maxBufferSize];
	}

	Buffer::Buffer(const Buffer& other)
		: buffer(nullptr),
		curBufferSize(other.curBufferSize),
		maxBufferSize(other.maxBufferSize)
	{
		if (maxBufferSize > 0)
		{
			buffer = new byte[maxBufferSize];
			memcpy(buffer, other.buffer, curBufferSize);
		}
	}

	Buffer::Buffer(Buffer&& other) noexcept
		: buffer(std::move(other.buffer)),
		curBufferSize(std::move(other.curBufferSize)),
		maxBufferSize(std::move(other.maxBufferSize))
	{
		other.buffer = nullptr;
	}

	Buffer& Buffer::operator=(const Buffer& other)
	{
		if (this == &other || maxBufferSize == other.maxBufferSize) return *this;
		if (buffer) delete[] buffer;

		curBufferSize = other.curBufferSize;
		maxBufferSize = other.maxBufferSize;

		if (buffer > 0)
		{
			buffer = new byte[maxBufferSize];
			memcpy(buffer, other.buffer, curBufferSize);
		}

		return *this;
	}

	Buffer& Buffer::operator=(Buffer&& other) noexcept
	{
		buffer = std::move(other.buffer);
		curBufferSize = std::move(other.curBufferSize);
		maxBufferSize = std::move(other.maxBufferSize);
		other.buffer = nullptr;
		return *this;
	}

	Buffer::~Buffer()
	{
		if (buffer)
			delete[] buffer;
	}

	Buffer& Buffer::operator<<=(size_t index) noexcept
	{
		curBufferSize -= index;
		memmove(buffer + index, buffer, curBufferSize);
	}

	Buffer& Buffer::operator>>=(size_t index) noexcept
	{
		curBufferSize += index;

		if (curBufferSize > maxBufferSize)
			curBufferSize = maxBufferSize;

		memmove(buffer, buffer + index, curBufferSize);
	}

	void Buffer::Set(size_t index, const char* content)
	{
		auto len = strnlen(content, maxBufferSize - index);
		auto size = len + index;

		if (curBufferSize < size)
			curBufferSize = size;

		memcpy(Get(index), content, len);
	}

	void Buffer::Set(size_t index, const char* content, size_t size)
	{
		if (index + size > maxBufferSize)
			throw std::logic_error{ Name{ "Size over buffer size" } };

		auto size = index + size;
		if (size > curBufferSize)
			curBufferSize = size;

		memcpy(Get(index), content, size);
	}
}