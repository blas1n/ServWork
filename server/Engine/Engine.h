#pragma once

#include "Core.h"

namespace ServWork
{
	class Engine final
	{
	public:
		Engine(class Reactor* reactor);
		~Engine();

		int Run();

	private:
		class ServerSocket* sock;
	};
}