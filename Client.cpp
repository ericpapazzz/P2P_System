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
        std::cerr << "Error al crear socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    //configurar la direccion del servidor
    server_address.sin_family = domain;
    server_address.sin_port = htons(port);

    // Convertir la dirección IP del servidor a binario
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
        std::cerr << "Error al conectarse al servidor: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return false;
    }
    std::cout << "Conexion exitosa!" << std::endl;
    return true;
    }

    bool Client::send_request(const char* request) {
        // Enviar la solicitud al servidor
        int send_result = send(client_socket, request, (int)strlen(request), 0);
        if (send_result == SOCKET_ERROR) {
            std::cerr << "Error al enviar la solicitud: " << WSAGetLastError() << std::endl;
            closesocket(client_socket);
            WSACleanup();
            return false;
        }

        std::cout << "Solicitud enviada: " << request << std::endl;

        // Cerrar el socket después de enviar
        closesocket(client_socket);
        return true;
    }

    // destructor
    Client::~Client() {
        closesocket(client_socket);
        WSACleanup();
    }