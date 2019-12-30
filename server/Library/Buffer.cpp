#include "Buffer.h"
#include <utility>

namespace ServWork
{
	Buffer::Buffer(size_t inBufferSize)
		: buffer(nullptr),
		bufferSize(inBufferSize)
	{
		if (buffer > 0)
			buffer = new byte[bufferSize];
	}

	Buffer::Buffer(const Buffer& other)
		: buffer(nullptr),
		bufferSize(other.bufferSize)
	{
		if (buffer > 0)
			buffer = new byte[bufferSize];
	}

	Buffer::Buffer(Buffer&& other) noexcept
		: buffer(std::move(other.buffer)),
		bufferSize(std::move(other.bufferSize))
	{
		other.buffer = nullptr;
	}

	Buffer& Buffer::operator=(const Buffer& other)
	{
		if (this == &other) return *this;
		if (buffer) delete[] buffer;

		bufferSize = other.bufferSize;

		if (buffer > 0)
			buffer = new byte[bufferSize];

		return *this;
	}

	Buffer& Buffer::operator=(Buffer&& other) noexcept
	{
		buffer = std::move(other.buffer);
		bufferSize = std::move(other.bufferSize);
		other.buffer = nullptr;
		return *this;
	}

	Buffer::~Buffer()
	{
		if (buffer)
			delete[] buffer;
	}
}