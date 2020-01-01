#include "Engine.h"
#include "Config.h"
#include "ServerSocket.h"
#include <iostream>
#include <Windows.h>

namespace ServWork
{
	Engine::Engine(Reactor* reactor, const UserData& data/*= UserData{ }*/)
		: sock{ new ServerSocket{ data } },
		sockIds(Config::maxUser)
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
			std::cout << "Cannot start ServWork : " << e.what() << std::endl;
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

	}

	void Engine::RegisterSocket(const Socket& socket)
	{
		sockIds.push_back(socket.GetId());
	}

	void Engine::UnregisterSocket(const Socket& socket)
	{
		auto iter = std::find(sockIds.cbegin(), sockIds.cend(), socket.GetId());
		sockIds.erase(iter);
	}
}