#include "TCP_Base.h"
#include <utility>
#include "INI.h"

TCP_Base::TCP_Base(int inPort, int inBufSize, int inQueueSize)
	: buf(nullptr),
	queueSize(inQueueSize),
	bufSize(inBufSize),
	port(inPort)
{
	buf = new char[bufSize];
}

TCP_Base::TCP_Base(const std::string& configPath)
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

TCP_Base::TCP_Base(TCP_Base&& other) noexcept
	: buf(std::move(other.buf)),
	queueSize(std::move(other.queueSize)),
	bufSize(std::move(other.bufSize)),
	port(std::move(other.port))
{
	other.buf = nullptr;
}

TCP_Base& TCP_Base::operator=(TCP_Base&& other) noexcept
{
	buf = std::move(other.buf);
	queueSize = std::move(other.queueSize);
	bufSize = std::move(other.bufSize);
	port = std::move(other.port);
	return *this;
}

TCP_Base::~TCP_Base()
{
	if (buf)
	{
		delete[] buf;
		buf = nullptr;
	}
}