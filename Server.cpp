#include "Server.h"
#include <iostream>

// Constructor del servidor
Server::Server(int domain, int service, int protocol, unsigned long interface_addr, int port, int backlog) {

    // Inicializar Winsock
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != 0) {
        std::cerr << "Error en WSAStartup: " << result << std::endl;
        exit(EXIT_FAILURE);
    }

    // Crear el socket
    server_socket = socket(domain, service, protocol);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "Error al crear el socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    server_address.sin_family = domain;
    server_address.sin_addr.s_addr = htonl(interface_addr);
    server_address.sin_port = htons(port);

    // Enlazar el socket con la dirección IP y puerto
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        std::cerr << "Error al enlazar socket: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Poner el servidor en modo escucha
    if (listen(server_socket, backlog) == SOCKET_ERROR) {
        std::cerr << "Error al poner socket en modo escucha: " << WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    std::cout << "Servidor iniciado en puerto: " << port << std::endl;
}

// Destructor
Server::~Server() {
    closesocket(server_socket);
    WSACleanup();
}
