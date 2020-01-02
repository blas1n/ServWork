#include "EventManager.h"
#include <algorithm>
#include "EventSocket.h"

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
		const auto index = WSAWaitForMultipleEvents
			(static_cast<DWORD>(ids.size()), events.data(), false, INFINITE, false);

		WSANETWORKEVENTS event;
		WSAEnumNetworkEvents(ids[index], events[index], &event);
		return std::make_tuple(index, event.lNetworkEvents);
	}
}