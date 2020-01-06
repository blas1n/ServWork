#include "Buffer.h"

namespace ServWork
{
	Buffer& Buffer::operator=(const char_t* content)
	{
		Init();
		Set(0, content);
		return *this;
	}

	Buffer& Buffer::operator=(const byte* content)
	{
		Init();
		Set(0, content);
		return *this;
	}

	Buffer& Buffer::operator+=(const char_t* content)
	{
		const auto len = strnlen(content, GetMaxSize() * sizeof(char_t));
		vec.insert(vec.cend(), content, content + len);
		return *this;
	}

	void Buffer::Set(size_t index, const byte* content, size_t size)
	{
		if (index < 0)
			index = GetCurSize() + index;

		const auto newSize = index + size;
		if (newSize > vec.size())
			vec.resize(newSize);

		std::copy(content, content + size, vec.begin() + index);
	}
}