#pragma once

#include "Def.h"
#include <mutex>
#include <vector>
#include <tuple>

namespace ServWork
{
	class EventManager final
	{
	public:
		EventManager(const EventManager&) = delete;
		EventManager(EventManager&&) = delete;

		static inline EventManager& Get()
		{
			static EventManager instance;
			return instance;
		}
		
		void RegisterEvent(const class EventSocket& socket, long event);
		void UnregisterEvent(const EventSocket& socket);
		void ChangeEvent(const EventSocket& socket, long event);
		
		std::tuple<DWORD, long> GetNetworkEvent() noexcept;

		inline SockId GetId(size_t index) const noexcept { return ids[index]; }

		inline size_t GetSize() const noexcept { return ids.size(); }

	private:
		EventManager() = default;
		~EventManager() = default;

	private:
		std::vector<SockId> ids;
		std::vector<HANDLE> events;
		std::mutex mutex;
	};
}