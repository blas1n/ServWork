#include "ServerSocket.h"
#include <algorithm>
#include "Config.h"
#include "EventManager.h"
#include "Name.h"
#include "Reactor.h"
#include "StringTranslator.h"

namespace ServWork
{
	ServerSocket::ServerSocket()
		: Base(), clients(Config::maxUser), clientNum(0) {}

	void ServerSocket::Open()
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			throw Error
			{
				Name{ "socket_error" }.Get() + strerror(errno)
			};
		}

		AddrIn addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(Config::port);
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

		int check = bind(s, reinterpret_cast<Addr*>(&addr), sizeof(addr));
		if (check == SOCKET_ERROR)
		{
			throw Error
			{
				Name{ "bind_error" }.Get() + strerror(errno)
			};
		}

		check = listen(s, Config::queueSize);
		if (check == SOCKET_ERROR)
		{
			throw Error
			{
				Name{ "listen_error" }.Get() + strerror(errno)
			};
		}

		Base::Open();
	}

	void ServerSocket::Close() noexcept
	{
		while (clientNum--)
			clients[clientNum].Close();

		LINGER linger{ 1, 0 };
		setsockopt(s, SOL_SOCKET, SO_LINGER,
			reinterpret_cast<char*>(&linger), sizeof(LINGER));

		Base::Close();
	}

	void ServerSocket::OnAccept()
	{
		AddrIn addr;
		SockLen len = sizeof(AddrIn);

		auto newSocket = accept(s, reinterpret_cast<Addr*>(&addr), &len);

		if (newSocket == INVALID_SOCKET)
			throw Warning{ Name{ "accepted_socket_is_invalid" } };

		wchar_t ip[16];
		StringTranslator::AsciiToUnicode(inet_ntoa(addr.sin_addr), ip);

		if (EventManager::Get().GetSize() == Config::maxUser)
		{
			reactor->OnLimitError(ip);
			closesocket(newSocket);
			throw Warning{ Name{ "client_is_full" } };
		}

		auto client = clients[clientNum++];
		client.Open();
		client.GetData().SetIp(ip);
	}

	size_t ServerSocket::FindClientIndex(SockId sock) const
	{
		auto iter = std::find_if(clients.begin(), clients.end(), [](auto client)
			{
				return client.GetId() == sock;
			});

		if (iter == clients.end())
			throw Warning{ Name{ "the_client_does_not_exist" } };
		
		return iter - clients.cbegin();
	}
}