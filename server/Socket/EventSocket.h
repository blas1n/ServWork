#pragma once

#include "Socket.h"

namespace ServWork
{
	class EventSocket : public Socket
	{
		using Base = Socket;

	public:
		EventSocket(SockId id = INVALID_SOCKET);

		EventSocket(const EventSocket&) = default;
		EventSocket(EventSocket&&) noexcept = default;

		EventSocket& operator=(const EventSocket&) = default;
		EventSocket& operator=(EventSocket&&) = default;

		~EventSocket() override = default;

		void Open() override;
		void Close() noexcept override;

		virtual void OnAccept();
		virtual void OnReceive();
		virtual void OnClose();

		inline class Reactor* GetReactor() const noexcept { return reactor; }
		inline void SetReactor(Reactor* inReactor) noexcept { reactor = inReactor; }

		virtual inline long GetEvent() const noexcept { return 0; }

	private:
		void ProcessRecvEvent();

	protected:
		Reactor* reactor;
	};
}