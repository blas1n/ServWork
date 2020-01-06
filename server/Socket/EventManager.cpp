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
		std::lock_guard<std::mutex> lock{ mutex };
		const auto id = socket.GetId();
		ids.push_back(id);
		
		auto handle = WSACreateEvent();
		WSAEventSelect(id, handle, event);
		events.push_back(handle);
	}

	void EventManager::UnregisterEvent(const EventSocket& socket)
	{
		std::lock_guard<std::mutex> lock{ mutex };
		const auto [idIter, eventIter] = Internal::GetHandles(ids, events, socket);
		
		ids.erase(idIter);
		WSACloseEvent(*eventIter);
		events.erase(eventIter);
	}

	void EventManager::ChangeEvent(const EventSocket& socket, long event)
	{
		std::lock_guard<std::mutex> lock{ mutex };
		const auto [idIter, eventIter] = Internal::GetHandles(ids, events, socket);
		WSAEventSelect(*idIter, *eventIter, event);
	}

	std::tuple<DWORD, long> EventManager::GetNetworkEvent() noexcept
	{
		DWORD ret;

		while (true)
		{
			mutex.lock();

			ret = WSAWaitForMultipleEvents(static_cast<DWORD>(GetSize()),
				events.data(), false, 1000, false);

			mutex.unlock();

			if (ret != WSA_WAIT_TIMEOUT) break;
			std::this_thread::sleep_for(10ms);
		}

		WSANETWORKEVENTS event;
		WSAEnumNetworkEvents(ids[ret], events[ret], &event);
		return std::make_tuple(ret, event.lNetworkEvents);
	}
}