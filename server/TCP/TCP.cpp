#include "TCP.h"
#include <iostream>
#include <utility>
#include "INI.h"

TCP::TCP(int inPort, int inBufSize, int inQueueSize)
	: s(),
	buf(nullptr),
	queueSize(0),
	bufSize(0),
	port(0)
{
	Init(inPort, inBufSize, inQueueSize);
}

TCP::TCP(const std::string& configPath)
	: s(),
	buf(nullptr),
	queueSize(0),
	bufSize(0),
	port(0)
{
	INI ini{ configPath };
	Init
	(
		std::stoi(ini.Get("QueueSize")),
		std::stoi(ini.Get("BufferSize")),
		std::stoi(ini.Get("Port"))
	);
}

TCP::TCP(TCP&& other) noexcept
	: s(std::move(other.s)),
	buf(std::move(other.buf)),
	queueSize(std::move(other.queueSize)),
	bufSize(std::move(other.bufSize)),
	port(std::move(other.port))
{
	other.buf = nullptr;
}

TCP& TCP::operator=(TCP&& other) noexcept
{
	s = std::move(other.s);
	buf = std::move(other.buf);
	queueSize = std::move(other.queueSize);
	bufSize = std::move(other.bufSize);
	port = std::move(other.port);

	other.buf = nullptr;
	return *this;
}

TCP::~TCP()
{
	if (buf)
		delete[] buf;
}

void TCP::Run()
{
	AddrIn clientAddr;
	int clientLen = sizeof(clientAddr);

	while (true)
	{
		auto clientSocket = s.Accept(clientAddr, clientLen);
		std::cout << "New Client Connect: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
		const auto readLen = clientSocket.Recv(buf, bufSize);

		if (readLen > 0)
			AddTask(onAccept, std::move(clientSocket), buf);
	}
}

void TCP::Init(int inPort, int inBufSize, int inQueueSize)
{
	port = inPort;
	bufSize = inBufSize;
	queueSize = inQueueSize;

	s.Open(port, queueSize);
	buf = new std::byte[bufSize];
}