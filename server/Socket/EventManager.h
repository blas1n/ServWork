#pragma once

#include "Def.h"
#include <vector>

namespace ServWork
{
	class EventManager final
	{
	public:
		EventManager(const EventManager&) = delete;
		EventManager(EventManager&&) = delete;

		static EventManager& Get();
		
		void RegisterEvent(const class EventSocket& socket, long event);
		void UnregisterEvent(const class EventSocket& socket);
		void ChangeEvent(const class EventSocket& socket, long event);
		
		decltype(auto) GetNetworkEvent() noexcept;

		inline SockId GetId(size_t index) const noexcept { return ids[index]; }

		inline size_t GetSize() const noexcept { return ids.size(); }

	private:
		EventManager() = default;
		~EventManager() = default;
		
		decltype(auto) GetHandles(const class EventSocket& socket);

	private:
		std::vector<SockId> ids;
		std::vector<HANDLE> events;
	};
}