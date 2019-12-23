#include "TCP.h"
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include "Exception.h"
#include "INI.h"

TCP::TCP()
	: onAccept(), serverSocket(0)
{
	INI ini{ ConfigDir };
	port = std::stoi(ini.Get("Port"));
	size = std::stoi(ini.Get("MaxBuf"));

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == -1) throw SocketException{ "socket" };

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int check = bind(serverSocket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
	if (check > 0) throw SocketException{ "bind" };

	if (listen(serverSocket, 5)) throw SocketException{ "listen" };

	buf = new char[size];
}

TCP::~TCP()
{
	close(serverSocket);
	delete[] buf;
}

void TCP::Run()
{
	struct sockaddr_in clientAddr;
	auto clientLen = sizeof(clientAddr);

	while (true)
	{
		auto clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientLen);
		std::cout << "New Client Connect: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
		const auto readLen = read(clientSocket, buf, size);

		if (readLen > 0)
		{
			onAccept(buf);
		}
		else
		{
			close(clientSocket);
			break;
		}

		close(clientSocket);
	}
}
