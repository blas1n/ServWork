#include "Engine.h"
#include <functional>
#include <iostream>
#include <map>
#include <Windows.h>
#include "Config.h"
#include "EventManager.h"
#include "ServerSocket.h"

namespace ServWork
{
	Engine::Engine(Reactor* reactor)
		: sock{ new ServerSocket }
	{
		WSADATA wsa;
		WSAStartup(MAKEWORD(2, 2), &wsa);

		try
		{
			Config::Init();
			sock->SetReactor(reactor);
			sock->Open();
		}
		catch (std::exception& e)
		{
			std::cout << Name{ "cannot_start" }.Get() << e.what() << std::endl;
		}
	}

	Engine::~Engine()
	{
		sock->Close();
		WSACleanup();
		delete sock;
	}

	int Engine::Run()
	{
		std::map<long, void(EventSocket::*)()> func
		{
			std::make_pair(FD_ACCEPT, &EventSocket::OnAccept),
			std::make_pair(FD_READ, &EventSocket::OnReceive),
			std::make_pair(FD_CLOSE, &EventSocket::OnClose)
		};

		while (true)
		{
			const auto [index, event] = EventManager::Get().GetNetworkEvent();
			
			EventSocket& socket = *sock;
			if (index > 0)
			{
				const auto id = EventManager::Get().GetId(index);
				socket = sock->FindClient(id);
			}

			func[event](socket);
		}

		return 0;
	}
}