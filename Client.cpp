#include "Client.h"
#include <iostream>

// contructor del cliente
Client::Client(int domain, int service, int protocol, const char* server_ip, int port) {
	
	// inicializar winstock
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        std::cerr << "Error en WSAStartup: " << result << std::endl;
        exit(EXIT_FAILURE);
    }

    // crear el socket
    client_socket = socket(domain, service, protocol);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "Error al crear socket: " << WSAGetLastError << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    //configurar la direccion del servidor
    server_address.sin_family = domain;
    server_address.sin_family = htons(port);

    // Convertir la dirección IP del servidor
    if (inet_pton(domain,server_ip,&server_address.sin_addr)<=0)
    {
        std::cerr << "Direccion IP no valida o no aceptada: " << WSAGetLastError()<<std::endl;
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

    // metodo para conectar al servidor
    bool Client::connect_to_server() {
    int result = connect(client_socket,(struct sockaddr*)&server_address, sizeof(server_address));
    if (result==SOCKET_ERROR)
    {
        std::cerr << "Error al conectarse al servidor: " << WSAGetLastError << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return false;
    }
    std::cout << "Conexion exitosa!" << std::endl;
    return true;
    }

    // destructor
    Client::~Client() {
        closesocket(client_socket);
        WSACleanup;
    }