#pragma once

#include "UserData.h"
#include <vector>

namespace ServWork
{
	class Engine final
	{
	public:
		Engine(class Reactor* reactor, const UserData& data = UserData{ });
		~Engine();

		int Run();

		void RegisterSocket(const class Socket& socket);
		void UnregisterSocket(const class Socket& socket);
		
	private:
		class ServerSocket* sock;

		std::vector<SockId> sockIds;
	};
}