#include "Base_TCP.h"
#include "INI.h"
#include "ThreadPool.h"

Base_TCP::Base_TCP()
{
	INI ini{ ConfigDir };
	port = std::stoi(ini.Get("Port"));
	bufSize = std::stoi(ini.Get("BufferSize"));
	queueSize = std::stoi(ini.Get("QueueSize"));

	threadPool = new ThreadPool;
	buf = new char[bufSize];
}

Base_TCP::~Base_TCP()
{
	delete threadPool;
	delete[] buf;
}