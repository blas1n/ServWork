#include "Base_TCP.h"
#include "INI.h"
#include "ThreadPool.h"

Base_TCP::Base_TCP()
	: onAccept()
{
	INI ini{ ConfigDir };
	port = std::stoi(ini.Get("Port"));
	size = std::stoi(ini.Get("MaxBuf"));

	threadPool = new ThreadPool;
	buf = new char[size];
}

Base_TCP::~Base_TCP()
{
  delete ThreadPool;
	delete[] buf;
}