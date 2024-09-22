// P2P_System.cpp
#include <iostream>
#include <thread>
#include "Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Enlazar con la biblioteca Winsock

// funcion que correra el server en un thread separado
void* server_function(void *arg) {
	//Server server(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 1248, 20);
	return NULL;
}

int main()
{
	// crear thread para el server
	std::thread server_thread(server_function);

	// esperar a que el thread termine
	server_thread.join();

	return 0;
}	