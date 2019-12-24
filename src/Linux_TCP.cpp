#if PLATFORM_LINUX

#include "Linux_TCP.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "Exception.h"

Linux_TCP::Linux_TCP()
	: Base_TCP(), serverSocket(0)
{
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
}

Linux_TCP::~Linux_TCP()
{
	close(serverSocket);
}

void Linux_TCP::Run()
{
	struct sockaddr_in clientAddr;
	auto clientLen = sizeof(clientAddr);

	while (true)
	{
		auto clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientLen);
		std::cout << "New Client Connect: " << inet_ntoa(clientAddr.sin_addr) << std::endl;
		const auto readLen = read(clientSocket, buf, size);

		if (readLen > 0)
			threadPool->AddTask(onAccept, clientSocket, buf);
    
    close(clientSocket);

    if (readLen == 0)
      break;
	}
}

#endif