#include "EventManager.h"
#include <algorithm>
#include <chrono>
#include <thread>
#include "EventSocket.h"

using namespace std::chrono_literals;

namespace ServWork
{
	namespace Internal
	{
		decltype(auto) GetHandles(const std::vector<SockId>& ids,
			std::vector<HANDLE>& events, const EventSocket& socket)
		{
			const auto idIter = std::find(ids.cbegin(), ids.cend(), socket.GetId());
			const auto eventIter = (idIter - ids.cbegin()) + events.cbegin();
			return std::make_tuple(idIter, eventIter);
		}
	}

	void EventManager::RegisterEvent(const EventSocket& socket, long event)
	{
		const auto id = socket.GetId();
		ids.push_back(id);
		
		auto handle = WSACreateEvent();
		WSAEventSelect(id, handle, event);
		events.push_back(handle);
	}

	void EventManager::UnregisterEvent(const EventSocket& socket)
	{
		const auto [idIter, eventIter] = Internal::GetHandles(ids, events, socket);
		if (idIter == ids.cend() || eventIter == events.cend())
			return;

		ids.erase(idIter);
		WSACloseEvent(*eventIter);
		events.erase(eventIter);
	}

	void EventManager::ChangeEvent(const EventSocket& socket, long event)
	{
		const auto [idIter, eventIter] = Internal::GetHandles(ids, events, socket);
		WSAEventSelect(*idIter, *eventIter, event);
	}

	std::tuple<DWORD, long> EventManager::GetNetworkEvent() noexcept
	{
		DWORD ret = WSAWaitForMultipleEvents(static_cast<DWORD>(GetSize()),
				events.data(), false, INFINITE, false);

		WSANETWORKEVENTS event;
		WSAEnumNetworkEvents(ids[ret], events[ret], &event);
		return std::make_tuple(ret, event.lNetworkEvents);
	}
}