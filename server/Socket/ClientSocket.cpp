#include "ClientSocket.h"
#include <iostream>
#include "Config.h"
#include "EventManager.h"
#include "Reactor.h"

namespace ServWork
{
	void ClientSocket::OnAccept()
	{
		std::cout << data->GetIp() << " was connected." << std::endl;
		reactor->OnAccept(*this);
	}

	void ClientSocket::OnReceive()
	{
		EventManager::Get().ChangeEvent(*this, GetEvent() | ~FD_READ);

		uint8 key = 0;
		recv(s, reinterpret_cast<char*>(&key), 1, 0);

		if (key != Config::checkKey)
		{
			Close();
			return;
		}

		uint8 id = 0;
		recv(s, reinterpret_cast<char*>(&id), 1, 0);

		uint32 size = 0;
		recv(s, reinterpret_cast<char*>(&size), sizeof(uint32), 0);
		size = Internal::SwapData(size);

		Buffer buf{ size };
		if (size > 0) Recv(buf, size);

		std::cout << data->GetIp() << " was recieved." << std::endl;
		reactor->OnReceive(*this, id, std::move(buf));
		EventManager::Get().ChangeEvent(*this, GetEvent());
	}

	void ClientSocket::OnClose()
	{
		std::cout << data->GetIp() << " was closed." << std::endl;
		reactor->OnClose(*this);
	}
}