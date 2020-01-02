#include "Engine.h"
#include <functional>
#include <iostream>
#include <map>
#include "Config.h"
#include "EventManager.h"
#include "ServerSocket.h"
#include "ThreadPool.h"

namespace ServWork
{
	Engine::Engine(Reactor* reactor)
		: sock{ new ServerSocket }
	{
		WSADATA wsa;
		if (!WSAStartup(MAKEWORD(2, 2), &wsa))
		{
			std::cout << Name{ "cannot_start_up_wsa" }.Get() << std::endl;
			exit(3);
		}

		try
		{
			setlocale(LC_ALL, "");
			Config::Init();
			sock->SetReactor(reactor);
			sock->Open();
		}
		catch (std::exception& e)
		{
			std::cout << Name{ "cannot_start" }.Get() << e.what() << std::endl;
			exit(2);
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
		std::map<long, std::function<void(EventSocket&)>> func
		{
			std::make_pair(FD_ACCEPT, &EventSocket::OnAccept),
			std::make_pair(FD_READ, &EventSocket::OnReceive),
			std::make_pair(FD_CLOSE, &EventSocket::OnClose)
		};

		ThreadPool threadPool;

		while (true)
		{
			const auto [index, event] = EventManager::Get().GetNetworkEvent();
			
			EventSocket& socket = *sock;
			if (index > 0)
			{
				const auto id = EventManager::Get().GetId(index);
				socket = sock->FindClient(id);
			}
			
			try
			{
				threadPool.AddTask(func[event], socket);
			}
			catch (Warning& e)
			{
				std::cout << e.what() << std::endl;
				continue;
			}
			catch (Error& e)
			{
				std::cout << e.what() << std::endl;
				exit(1);
			}
		}

		return 0;
	}
}