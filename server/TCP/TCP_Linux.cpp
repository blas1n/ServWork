#if PLATFORM_LINUX

#include "TCP_Linux.h"
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
#include "ThreadPool.h"

TCP_Linux::TCP_Linux(int inPort, int inBufSize, int inQueueSize)
	: TCP_Base(inPort, inBufSize, inQueueSize), onAccept(), serverSocket(0)
{
	Init();
}

TCP_Linux::TCP_Linux(const std::string& configPath)
	: TCP_Base(configPath), onAccept(), serverSocket(0)
{
	Init();
}

TCP_Linux::TCP_Linux(TCP_Linux&& other) noexcept
	: TCP_Base(std::move(other)),
	onAccept(std::move(other.onAccept)),
	serverSocket(std::move(other.serverSocket))
{}

TCP_Linux& TCP_Linux::operator=(TCP_Linux&& other) noexcept
{
	TCP_Base::operator=(std::move(other));
	onAccept = std::move(other.onAccept);
	serverSocket = std::move(other.serverSocket);
	return *this;
}

TCP_Linux::~TCP_Linux()
{
	close(serverSocket);
}

void TCP_Linux::Run()
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
			AddTask(onAccept, clientSocket, buf);

		close(clientSocket);
	}
}

void TCP_Linux::Init()
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

#endif