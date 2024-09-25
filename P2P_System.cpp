// P2P_System.cpp
#include <iostream>
#include <thread>
#include "Server.h"
#include "Client.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")  // Enlazar con la biblioteca Winsock

// funcion que correra el server en un thread separado
static void* server_function(void *arg) {
	Server server(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 1248, 20);
	sockaddr* address = (struct sockaddr*)&server.server_address;
	int address_len = sizeof(server.server_address);

	
	while (true)
	{
		SOCKET client_socket = accept(server.server_socket, address, &address_len); // aceptar conexion del cliente
		if (client_socket==INVALID_SOCKET)
		{
			std::cerr << "Error al aceptar conexion: " << WSAGetLastError() << std::endl;
			continue;
		}

		// leer el request
		char request[255];
		memset(request, 0, sizeof(request));

		int bytes_received = recv(client_socket, request, sizeof(request), 0);
		if (bytes_received == SOCKET_ERROR)
		{
			std::cerr << "Error al recibir datos: " << WSAGetLastError() << std::endl;
		}
		else {
			std::cout << "Request recibido: " << request << std::endl;
		}

		// enviar respuesta
		const char* response = "Mensaje recibido";
		send(client_socket, response, (int)strlen(response), 0);

		//cerrar conexion con el cliente
		closesocket(client_socket);
		
	}
	return NULL;
}

static void client_function(char* request) {
	Client client(AF_INET, SOCK_STREAM, 0, "127.0.0.1", 1248);
	client.send_request(request);
}


int main()
{
	// crear thread para el server
	std::thread server_thread(server_function);

	// esperar a que el thread termine
	server_thread.join();

	while (true)
	{
		char request[255];
		memset(request,0, 255);
		fgets(request, 255, stdin);
		client_function(request);
	}

	return 0;
}	