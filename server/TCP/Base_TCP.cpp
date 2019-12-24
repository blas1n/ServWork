#include "Base_TCP.h"
#include <utility>
#include "INI.h"

Base_TCP::Base_TCP()
	: buf(nullptr),
	queueSize(0),
	bufSize(0),
	port(0)
{
	INI ini{ ConfigDir };
	port = std::stoi(ini.Get("Port"));
	bufSize = std::stoi(ini.Get("BufferSize"));
	queueSize = std::stoi(ini.Get("QueueSize"));

	buf = new char[bufSize];
}

Base_TCP::Base_TCP(const Base_TCP& other)
	: buf(nullptr),
	queueSize(other.queueSize),
	bufSize(other.bufSize),
	port(other.port)
{
	buf = new char[bufSize];
}

Base_TCP::Base_TCP(Base_TCP&& other) noexcept
	: buf(std::move(other.buf)),
	queueSize(std::move(other.queueSize)),
	bufSize(std::move(other.bufSize)),
	port(std::move(other.port))
{
	other.buf = nullptr;
}

Base_TCP& Base_TCP::operator=(const Base_TCP& other)
{
	queueSize = other.queueSize;
	bufSize = other.bufSize;
	port = other.port;

	if (buf)
		delete[] buf;

	buf = new char[bufSize];
}

Base_TCP& Base_TCP::operator=(Base_TCP&& other) noexcept
{
	buf = std::move(other.buf);
	queueSize = std::move(other.queueSize);
	bufSize = std::move(other.bufSize);
	port = std::move(other.port);
}

Base_TCP::~Base_TCP()
{
	if (buf)
	{
		delete[] buf;
		buf = nullptr;
	}
}