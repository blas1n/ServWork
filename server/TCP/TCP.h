#pragma once

#include "Socket.h"
#include <functional>
#include <string>

namespace ServWork
{
	class TCP final
	{
	public:
		TCP(int inPort, int inQueueSize);
		TCP(const std::string& configPath);

		TCP(const TCP&) = delete;
		TCP(TCP&& other) noexcept = default;

		TCP& operator=(const TCP&) = delete;
		TCP& operator=(TCP&& other) noexcept = default;

		~TCP() = default;

		void Run();

		template <class Fn>
		inline void SetOnAccept(Fn&& fn)
		{
			onAccept = fn;
		}

		inline int GetPort() const noexcept
		{
			return port;
		}

		inline int GetQueueSize() const noexcept
		{
			return queueSize;
		}

	private:
		void Init(int inPort, int inQueueSize);

	private:
		std::function<void(Socket)> onAccept;

		Socket s;
		int queueSize;
		int port;
	};
}