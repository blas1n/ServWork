#pragma once

#include "BaseSocket.h"
#include "Reactor.h"

namespace ServWork
{
	class ReactableSocket : public BaseSocket
	{
	public:
		ReactableSocket(SockId id = INVALID_SOCKET);

		ReactableSocket(const ReactableSocket&) = default;
		ReactableSocket(ReactableSocket&&) noexcept = default;

		ReactableSocket& operator=(const ReactableSocket&) = default;
		ReactableSocket& operator=(ReactableSocket&&) = default;

		~ReactableSocket() override = default;

		void ProcessRecvEvent();

		inline void SetHandle(HWND inHandle) noexcept { handle = inHandle; }

		inline Reactor* GetReactor() const noexcept
		{
			return reactor;
		}

		inline void SetReactor(Reactor* inReactor) noexcept
		{
			reactor = inReactor;
		}

	protected:
		HWND handle;
		Reactor* reactor;
	};
}