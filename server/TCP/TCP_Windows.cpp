#if PLATFORM_WINDOWS

#include "TCP_Windows.h"
#include <iostream>
#include <WS2tcpip.h>
#include "ThreadPool.h"

TCP_Windows::TCP_Windows(int inPort, int inBufSize, int inQueueSize)
	: Base_TCP(inPort, inBufSize, inQueueSize), onAccept(), serverSocket(0)
{
	Init();
}

TCP_Windows::TCP_Windows(const std::string& configPath)
	: Base_TCP(configPath), onAccept(), serverSocket(0)
{
	Init();
}

TCP_Windows::TCP_Windows(TCP_Windows&& other) noexcept
	: Base_TCP(std::move(other)),
	onAccept(std::move(other.onAccept)),
	serverSocket(std::move(other.serverSocket))
{}

TCP_Windows& TCP_Windows::operator=(TCP_Windows&& other) noexcept
{
	Base_TCP::operator=(std::move(other));
	onAccept = std::move(other.onAccept);
	serverSocket = std::move(other.serverSocket);
	return *this;
}

TCP_Windows::~TCP_Windows()
{
	closesocket(serverSocket);
	WSACleanup();
}

void TCP_Windows::Run()
{
	SOCKADDR_IN clientAddr;
	int clientLen = sizeof(clientAddr);

	while (true)
	{
		SOCKET clientSocket = accept(serverSocket, reinterpret_cast<SOCKADDR*>(&clientAddr), &clientLen);
		if (clientSocket == INVALID_SOCKET)
		{
			throw std::runtime_error
			{
				std::string("invalid socket ") + strerror(errno)
			};
		}
		
		std::cout << "New Client Connect: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
		const auto readLen = recv(clientSocket, buf, bufSize, 0);

		if (readLen > 0)
			AddTask(onAccept, clientSocket, buf);

		closesocket(clientSocket);
	}
}

void TCP_Windows::Init()
{
	WSADATA wsaData;

	int check = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (check != NO_ERROR)
	{
		throw std::runtime_error
		{
			std::string("WSAStartup error ") + strerror(errno)
		};
	}

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		throw std::runtime_error
		{
			std::string("socket error ") + strerror(errno)
		};
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	check = bind(serverSocket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr));
	if (check == SOCKET_ERROR)
	{
		throw std::runtime_error
		{
			std::string("bind error ") + strerror(errno)
		};
	}

	check = listen(serverSocket, queueSize);
	if (check == SOCKET_ERROR)
	{
		throw std::runtime_error
		{
			std::string("listen error ") + strerror(errno)
		};
	}
}

#endif