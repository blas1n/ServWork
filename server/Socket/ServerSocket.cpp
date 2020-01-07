#define _CRT_SECURE_NO_WARNING

#include "ServerSocket.h"
#include <algorithm>
#include "Config.h"
#include "EventManager.h"
#include "Reactor.h"

namespace ServWork
{
	ServerSocket::ServerSocket()
		: Base(),
		clients(std::make_shared<std::vector<ClientSocket>>(Config::maxUser)) {}

	void ServerSocket::Open()
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			throw Error
			{
				Name{ STR("socket_error") }.Get() + strerror(errno)
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
				Name{ STR("bind_error") }.Get() + strerror(errno)
			};
		}

		check = listen(s, Config::queueSize);
		if (check == SOCKET_ERROR)
		{
			throw Error
			{
				Name{ STR("listen_error") }.Get() + strerror(errno)
			};
		}

		Base::Open();
	}

	void ServerSocket::Close() noexcept
	{
		for (auto& client : *clients)
			client.Close();

		LINGER linger{ 1, 0 };
		setsockopt(s, SOL_SOCKET, SO_LINGER,
			reinterpret_cast<char*>(&linger), sizeof(LINGER));

		Base::Close();
	}

	void ServerSocket::Connect()
	{
		AddrIn addr;
		SockLen len = sizeof(AddrIn);

		auto newSocket = accept(s, reinterpret_cast<Addr*>(&addr), &len);

		if (newSocket == INVALID_SOCKET)
			throw MakeWarning("accepted_socket_is_invalid");

		auto ip = std::string(inet_ntoa(addr.sin_addr));

		if (EventManager::Get().GetSize() == Config::maxUser)
		{
			reactor->OnLimitError(ip.c_str());
			closesocket(newSocket);
			throw MakeWarning("client_is_full");
		}

		ClientSocket client{ };
		client.GetData().SetIp(ip.c_str());
		client.SetReactor(reactor);
		client.SetId(newSocket);
		client.Open();
		clients->emplace_back(std::move(client)).OnAccept();
	}

	void ServerSocket::Disconnect(ClientSocket& client)
	{
		auto iter = std::find(clients->begin(), clients->end(), client);
		auto elem = std::move(*iter);
		clients->erase(iter);

		elem.OnClose();
	}

	size_t ServerSocket::FindClientIndex(SockId sock) const
	{
		auto iter = std::find_if(clients->begin(), clients->end(), [sock](auto& client)
		{
			return client.GetId() == sock;
		});

		if (iter == clients->end())
			throw MakeWarning("the_client_does_not_exist");
		
		return iter - clients->cbegin();
	}
}