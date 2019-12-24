#include "TCP.h"
#include <iostream>

void Test(int socket, char* content)
{
	std::cout << content << std::endl;
}

int main()
{
	TCP tcp;
	tcp.SetOnAccept(Test);
	tcp.Run();
	return 0; 
}
