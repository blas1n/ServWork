#include "ServerSocket.h"
#include "Config.h"
#include "UserData.h"
#include "StringTranslator.h"

namespace ServWork
{
	ServerSocket::ServerSocket(UserData* proto)
		: ReactableSocket(), users(nullptr)
	{
		users = new UserData*[Config::maxUser];

		for (int i = 0; i < Config::maxUser; ++i)
			users[i] = proto->Clone();
	}

	ServerSocket::~ServerSocket()
	{
		for (int i = 0; i < Config::maxUser; ++i)
			delete users[i];

		delete[] users;
	}

	void ServerSocket::Open()
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			throw std::runtime_error
			{
				std::string("socket error ") + strerror(errno)
			};
		}

		AddrIn addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(Config::port);

#if PLATFORM_WINDOWS
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
#elif PLATFORM_LINUX
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif

		int check = bind(s, reinterpret_cast<Addr*>(&addr), sizeof(addr));
		if (check == SOCKET_ERROR)
		{
			throw std::runtime_error
			{
				std::string("bind error ") + strerror(errno)
			};
		}

		check = listen(s, Config::queueSize);
		if (check == SOCKET_ERROR)
		{
			throw std::runtime_error
			{
				std::string("listen error ") + strerror(errno)
			};
		}

		::WSAAsyncSelect(s, handle, Config::acceptId, GetDefaultEvent());
	}

	void ServerSocket::Close()
	{
		if (s == INVALID_SOCKET)
			return;

		LINGER linger{ 1, 0 };
		setsockopt(s, SOL_SOCKET, SO_LINGER,
			reinterpret_cast<char*>(&linger), sizeof(LINGER));

#if PLATFORM_WINDOWS
		closesocket(s);
#elif PLATFORM_LINUX
		close(s);
#endif

		s = INVALID_SOCKET;
	}

	int ServerSocket::OnAccept(WPARAM wParam, LPARAM lParam)
	{
		AddrIn addr;
		SockLen len = sizeof(AddrIn);

		auto newSocket = accept(static_cast<SOCKET>(wParam),
			reinterpret_cast<Addr*>(&addr), &len);

		if (newSocket == INVALID_SOCKET) return -1;

		uint32 i;
		wchar_t ip[16];
		StringTranslator::AsciiToUnicode(inet_ntoa(addr.sin_addr), ip);

		for (i = 0; i < Config::maxUser; ++i)
		{
			if (users[i]->GetSocket() == INVALID_SOCKET)
				continue;

			auto user = users[i];
			user->SetSocket(newSocket);
			user->SetIp(ip);

			::WSAAsyncSelect(newSocket, handle, Config::notifyId, GetDefaultEvent() | FD_READ);
			reactor->OnAccept(user);
			break;
		}

		if (i == Config::maxUser)
		{
			reactor->OnLimitError(ip);
			closesocket(newSocket);
			return -2;
		}

		return 1;
	}

	void ServerSocket::OnEvent(WPARAM wParam, LPARAM lParam)
	{
		auto sock = static_cast<SockId>(wParam);

		if (WSAGETSELECTEVENT(lParam) == FD_READ)
		{
			ReactableSocket(sock).ProcessRecvEvent();
			return;
		}
		
		auto user = FindUserData(sock);
		reactor->OnClose(user);
		closesocket(user->GetSocket());
	}

	int ServerSocket::FindUserIndex(SockId sock)
	{
		for (uint32 i = 0; i < Config::maxUser; ++i)
			if (users[i]->GetSocket() == sock)
				return i;
		return -1;
	}

	UserData* ServerSocket::FindUserData(SockId sock)
	{
		for (uint32 i = 0; i < Config::maxUser; ++i)
			if (users[i]->GetSocket() == sock)
				return users[i];
		return nullptr;
	}
}