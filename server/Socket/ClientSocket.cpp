#include "ClientSocket.h"
#include <algorithm>
#include "Config.h"
#include "Name.h"
#include "UserData.h"

namespace ServWork
{
	ClientSocket::ClientSocket(wchar_t* ip)
		: Base(), data(new UserData(ip)) {}

	ClientSocket::~ClientSocket()
	{
		delete data;
	}

	void ClientSocket::Close()
	{
		if (s == INVALID_SOCKET)
			return;

		Base::Close();

		LINGER linger{ 1, 0 };
		setsockopt(s, SOL_SOCKET, SO_LINGER,
			reinterpret_cast<char*>(&linger), sizeof(LINGER));

		closesocket(s);
		s = INVALID_SOCKET;
	}

	void ClientSocket::OnAccept()
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

		clients.emplace_back(ip);
	}

	size_t ClientSocket::FindClientIndex(SockId sock) const
	{
		return GetClient(sock) - clients.cbegin();
	}

	const ClientSocket& ClientSocket::FindClient(SockId sock) const
	{
		return *GetClient(sock);
	}

	decltype(auto) ClientSocket::GetClient(SockId sock) const
	{
		auto iter = std::find_if(clients.begin(), clients.end(), [](auto client)
			{
				return client.GetId() == sock;
			});

		if (iter == clients.end())
			throw Warning{ Name{ "the_client_does_not_exist" } };

		return iter;
	}
}