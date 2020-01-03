#pragma once

#include "Socket.h"

namespace ServWork
{
	class EventSocket : public Socket
	{
		using Base = Socket;

	public:
		EventSocket();

		EventSocket(const EventSocket&) = default;
		EventSocket(EventSocket&&) noexcept = default;

		EventSocket& operator=(const EventSocket&) = default;
		EventSocket& operator=(EventSocket&&) = default;

		~EventSocket() override = default;

		void Open() override;
		void Close() noexcept override;

		inline class Reactor* GetReactor() const noexcept { return reactor; }
		inline void SetReactor(Reactor* inReactor) noexcept { reactor = inReactor; }

		virtual inline long GetEvent() const noexcept { return 0; }

	protected:
		Reactor* reactor;
	};
}