#if PLATFORM_WINDOWS

#include "Windows_TCP.h"
#include <iostream>
#include <WS2tcpip.h>
#include "ThreadPool.h"

Windows_TCP::Windows_TCP()
	: Base_TCP(), onAccept(), serverSocket(0)
{
	try
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
		inet_pton(AF_INET, INADDR_ANY, &addr.sin_addr.S_un.S_addr);

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
	catch (std::runtime_error& e)
	{
		WSACleanup();
		throw e;
	}
}

Windows_TCP::~Windows_TCP()
{
	closesocket(serverSocket);
	WSACleanup();
}

void Windows_TCP::Run()
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

#endif