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
#include "Exception.h"
#include "INI.h"

TCP::TCP()
	: onAccept(), socket(0)
{
	INI ini{ ConfigDir };
	port = std::stoi(ini.Get("Port"));
	size = std::stoi(ini.Get("MaxBuf"));

	socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket == -1) throw SocketException{ "socket" };

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	int check = bind(socket, (struct sockaddr*) & addr, sizeof(addr));
	if (check > 0) throw SocketException{ "bind" };

	if (listen(socket, 5)) throw SocketException{ "listen" };

	buf = new char[size];
}

TCP::~TCP()
{
	close(socket);
	delete[] buf;
}

void TCP::Run()
{
	while (1)
	{
		int clientSocket = accept(socket, (struct sockaddr*) & clientaddr, &client_len);
		std::cout << "New Client Connect: " << inet_ntoa(clientaddr.sin_addr) << std::endl;
		read_len = read(clientSocket, buf, size);
		onAccept(buf);

	/* 파일명 받기 */

		if (read_len > 0)
		{
			memset(file_name, 0x00, MAXBUF);
			strcpy(file_name, buf);
			printf("%s > %s\n", inet_ntoa(clientaddr.sin_addr), file_name);
		}
		else
		{
			close(client_sockfd);
			break;
		}

		/* 파일 열기 */
		source_fd = open(file_name, O_RDONLY);
		if (!source_fd)
		{
			perror("file open error : ");
			break;
		}

		printf("before while\n");
		while (1)
		{
			memset(buf, 0x00, MAXBUF);
			file_read_len = read(source_fd, buf, MAXBUF);
			printf("\nread : %s", buf);
			chk_write = write(client_sockfd, buf, MAXBUF);

			if (file_read_len == EOF | file_read_len == 0)
			{
				printf("finish file\n");
				break;
			}
		}

		close(client_sockfd);
		close(source_fd);
	}
}