#pragma once

#include "Core.h"
#include <type_traits>
#include "Reactor.h"

namespace ServWork
{
	class EngineBase
	{
	public:
		EngineBase();
		virtual ~EngineBase();

		int Run();

	protected:
		ServerSocket* sock;
	};

	template <class T>
	class Engine final : public EngineBase
	{
	public:
		Engine()
			: EngineBase(),
			reactor(new T)
		{
			sock->SetReactor(reactor);
			reactor->SetServer(sock);
		}

		~Engine() override
		{
			delete reactor;
		}

	private:
		Reactor* reactor;
	};
}