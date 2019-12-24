#if PLATFORM_LINUX

#include "Linux_TCP.h"
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <errno.h>
#include <exception>
#include <iostream>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

Linux_TCP::Linux_TCP()
	: Base_TCP(), onAccept(), serverSocket(0)
{
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == -1)
	{
		throw std::runtime_error
		{
			std::string("socket error ") + strerror(errno)
		};
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int check = bind(serverSocket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
	if (check == -1)
	{
		throw std::runtime_error
		{
			std::string("bind error ") + strerror(errno)
		};
	}

	check = listen(serverSocket, queueSize);
	if (check == -1)
	{
		throw std::runtime_error
		{
			std::string("listen error ") + strerror(errno)
		};
	}
}

Linux_TCP::~Linux_TCP()
{
	close(serverSocket);
}

void Linux_TCP::Run()
{
	struct sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);

	while (true)
	{
		auto clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientLen);
		if (clientSocket == -1)
		{
			throw std::runtime_error
			{
				std::string("invalid socket ") + strerror(errno)
			};
		}

		std::cout << "New Client Connect: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
		const auto readLen = read(clientSocket, buf, bufSize);

		if (readLen > 0)
			threadPool->AddTask(onAccept, clientSocket, buf);

		close(clientSocket);
	}
}

#endif