#include <iostream>
#include <thread>

void* server_function(void *arg) {
	return NULL;
}

int main()
{
	Server server(AF_INET, SOCK_STREAM, 0, INADOR_ANY, 1248, 20);
	std::thread server_thread(server_function);
}	