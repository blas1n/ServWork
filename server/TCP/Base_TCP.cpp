#include "Base_TCP.h"
#include "INI.h"
#include "ThreadPool.h"

Base_TCP::Base_TCP(ThreadPool& inThreadPool)
	: threadPool(inThreadPool),
	buf(nullptr),
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

Base_TCP::~Base_TCP()
{
	delete[] buf;
}