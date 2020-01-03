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
	EngineBase::EngineBase()
		: sock{ new ServerSocket }
	{
		std::locale::global(std::locale(""));

		WSADATA wsa;
		if (!WSAStartup(MAKEWORD(2, 2), &wsa))
		{
			std::wcout << Name{ STR("cannot_start_up_wsa") }.Get() << std::endl;
			exit(3);
		}

		try
		{
			Config::Init();
			sock->Open();
		}
		catch (Exception& e)
		{
			std::wcout << Name{ STR("cannot_start") }.Get() << e.What() << std::endl;
			exit(2);
		}
	}

	EngineBase::~EngineBase()
	{
		sock->Close();
		WSACleanup();
		delete sock;
	}

	int EngineBase::Run()
	{
		std::map<long, std::function<void(ClientSocket&)>> func
		{
			std::make_pair(FD_READ, &ClientSocket::OnReceive),
			std::make_pair(FD_CLOSE, &ClientSocket::OnClose)
		};

		ThreadPool threadPool;

		while (true)
		{
			const auto [index, event] = EventManager::Get().GetNetworkEvent();
			
			if (event == FD_ACCEPT)
			{
				threadPool.AddTask(&ServerSocket::Accept, *sock);
				continue;
			}

			try
			{
				const auto id = EventManager::Get().GetId(index);
				auto& socket = sock->FindClient(id);
				threadPool.AddTask(func[event], socket);
			}
			catch (Warning& e)
			{
				std::wcout << e.What() << std::endl;
				continue;
			}
			catch (Error& e)
			{
				std::wcout << e.What() << std::endl;
				return 1;
			}
		}

		return 0;
	}
}