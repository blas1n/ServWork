#pragma once

#include <functional>
#include <string>

class Base_TCP
{
public:
	Base_TCP();
	virtual ~Base_TCP();

  inline int GetPort() const noexcept
  {
    return port;
  }

protected:
  class ThreadPool* threadPool;
  char* buf;
	int size;
  int port;

private:
	inline static const std::string ConfigDir = "../config.ini";
};

#endif