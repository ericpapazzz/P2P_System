#include <iostream>
#include <thread>

void* server_function(void *arg) {
	return NULL;
}

int main()
{
	std::thread server_thread(server_function);
}	