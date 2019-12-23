#include <functional>
#include <string>

class TCP
{
public:
	TCP();
	~TCP();

	void Run();

	template <class FN>
	inline void SetOnAccept(FN&& fn)
	{
		onAccept = fn;
	}

private:
	inline static const std::string ConfigDir = "../config.ini";

	std::function<void(int, char*)> onAccept;
	class ThreadPool* threadPool;
	int serverSocket;
	char* buf;
	int size;
	int port;
};
