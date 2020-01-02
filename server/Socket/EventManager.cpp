#include "EventManager.h"
#include <algorithm>
#include <tuple>
#include "EventSocket.h"

namespace ServWork
{
	EventManager& EventManager::Get()
	{
		static EventManager instance;
		return instance;
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
		const auto [idIter, eventIter] = GetHandles(socket);
		
		ids.erase(idIter);
		WSACloseEvent(*eventIter);
		events.erase(eventIter);
	}

	void EventManager::ChangeEvent(const EventSocket& socket, long event)
	{
		const auto [idIter, eventIter] = GetHandles(socket);
		WSAEventSelect(*idIter, *eventIter, event);
	}

	decltype(auto) EventManager::GetNetworkEvent() noexcept
	{
		const auto index = WSAWaitForMultipleEvents(ids.size(), events.data(), false, INFINITE, false);
		WSANETWORKEVENTS event;
		WSAEnumNetworkEvents(ids[index], events[index], &event);
		return std::make_tuple(index, event.lNetworkEvents);
	}

	decltype(auto) EventManager::GetHandles(const EventSocket& socket)
	{
		const auto idIter = std::find(ids.cbegin(), ids.cend(), socket.GetId());
		const auto eventIter = (idIter - ids.cbegin()) + events.cbegin();
		return std::make_tuple(idIter, eventIter);
	}
}