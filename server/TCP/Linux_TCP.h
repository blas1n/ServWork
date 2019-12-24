#if PLATFORM_LINUX

#pragma once

#include "Base_TCP.h"

class Linux_TCP : public Base_TCP
{
public:
	Linux_TCP(class ThreadPool& inThreadPool);
	~Linux_TCP();

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

private:
	std::function<void(int, char*)> onAccept;
	int serverSocket;
};

using TCP = Linux_TCP;

#endif