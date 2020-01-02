#pragma once

#include "Core.h"
#include "ThreadAccesser.h"

namespace ServWork
{
	class Engine final : private ThreadAccesser
	{
	public:
		Engine(class Reactor* reactor);
		~Engine();

		int Run();

	private:
		class ServerSocket* sock;
	};
}