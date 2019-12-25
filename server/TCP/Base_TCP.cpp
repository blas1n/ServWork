#include "Base_TCP.h"
#include <utility>
#include "INI.h"

Base_TCP::Base_TCP(int inPort, int inBufSize, int inQueueSize)
	: buf(nullptr),
	queueSize(inQueueSize),
	bufSize(inBufSize),
	port(inPort)
{
	buf = new char[bufSize];
}

Base_TCP::Base_TCP(const std::string& configPath)
	: buf(nullptr),
	queueSize(0),
	bufSize(0),
	port(0)
{
	INI ini{ configPath };
	port = std::stoi(ini.Get("Port"));
	bufSize = std::stoi(ini.Get("BufferSize"));
	queueSize = std::stoi(ini.Get("QueueSize"));

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

Base_TCP& Base_TCP::operator=(Base_TCP&& other) noexcept
{
	buf = std::move(other.buf);
	queueSize = std::move(other.queueSize);
	bufSize = std::move(other.bufSize);
	port = std::move(other.port);
	return *this;
}

Base_TCP::~Base_TCP()
{
	if (buf)
	{
		delete[] buf;
		buf = nullptr;
	}
}