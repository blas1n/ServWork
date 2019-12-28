#include "TCP.h"
#include <iostream>
#include <utility>
#include "INI.h"
#include "ThreadPool.h"

namespace ServWork
{
	TCP::TCP(int inPort,int inQueueSize)
		: s(),
		queueSize(0),
		port(0)
	{
		Init(inPort, inQueueSize);
	}

	TCP::TCP(const std::string& configPath)
		: s(),
		queueSize(0),
		port(0)
	{
		INI ini{ configPath };
		Init
		(
			std::stoi(ini.Get("Port")),
			std::stoi(ini.Get("QueueSize"))
		);
	}

	void TCP::Run()
	{
		AddrIn clientAddr;
		SockLen clientLen = sizeof(clientAddr);

		while (true)
		{
			auto clientSocket = s.Accept(clientAddr, clientLen);
			std::cout << "New Client Connect: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
			ThreadPool::Get().AddTask(onAccept, std::move(clientSocket));
		}
	}

	void TCP::Init(int inPort, int inQueueSize)
	{
		port = inPort;
		queueSize = inQueueSize;
		s.Open(port, queueSize);
	}
}