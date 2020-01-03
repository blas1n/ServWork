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
		class ServerSocket* sock;
	};

	template <class T, class = std::enable_if_t<std::is_base_of_v<Reactor, T>>>
	class Engine final : public EngineBase
	{
		Engine()
			: EngineBase(),
			reactor(new T{ sock }) {}

	private:
		T* reactor;
	};
}