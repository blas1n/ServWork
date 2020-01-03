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
				switch (event)
				{
				case FD_ACCEPT:
					threadPool.AddTask(&ServerSocket::Accept, socket);
					break;
				case FD_READ:
					threadPool.AddTask(&ClientSocket::OnReceive, socket);
					break;
				case FD_CLOSE:
					threadPool.AddTask(&ClientSocket::OnClose, socket);
					break;
				}
			}
			catch (Warning& e)
			{
				std::wcout << e.What() << std::endl;
				continue;
			}
			catch (Error& e)
			{
				std::wcout << e.What() << std::endl;
				exit(1);
			}
		}

		return 0;
	}
}