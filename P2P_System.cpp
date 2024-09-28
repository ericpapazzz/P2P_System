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
void server_function() {
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
		std::cout << request << std::endl;

		//cerrar conexion con el cliente
		closesocket(client_socket);
		
	}
}

void client_function(char* request) {
	Client client(AF_INET, SOCK_STREAM, 0, "192.168.1.66", 1248);
	client.send_request(request);
}


int main()
{
	// Crear thread para el server
	std::thread server_thread(server_function);

	// Esperar un momento para asegurarnos de que el servidor esté en escucha
	std::this_thread::sleep_for(std::chrono::seconds(1));

	// Iniciar la interacción del cliente
	while (true)
	{
		char request[255];
		memset(request, 0, 255);
		std::cout << "Ingrese su mensaje: "; // Mensaje para indicar que se puede ingresar
		fgets(request, 255, stdin);
		client_function(request);
	}

	// Esperar a que el thread termine (esto probablemente no se alcanzará en este bucle infinito)
	server_thread.join();

	return 0;
}	