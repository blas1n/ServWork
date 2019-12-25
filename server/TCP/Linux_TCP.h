#if PLATFORM_LINUX

#pragma once

#include "Base_TCP.h"

class Linux_TCP final : public Base_TCP
{
public:
	Linux_TCP(int inPort, int inBufSize, int inQueueSize);
	Linux_TCP(const std::string& configPath);

	Linux_TCP(Linux_TCP&& other) noexcept;
	Linux_TCP& operator=(Linux_TCP&& other) noexcept;

	~Linux_TCP() override;

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

private:
	void Init();

private:
	std::function<void(int, char*)> onAccept;
	int serverSocket;
};

using TCP = Linux_TCP;

#endif