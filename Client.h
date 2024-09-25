#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Enlazar con la biblioteca Winsock

class Client {
public:
    SOCKET client_socket;
    struct sockaddr_in server_address;

    // Constructor del cliente
    Client(int domain, int service, int protocol, const char* server_ip, int port);

    // Método para conectarse al servidor
    bool connect_to_server();

    // Método para enviar una solicitud al servidor
    bool send_request(const char* request);

    // Destructor
    ~Client();
};

#endif // CLIENT_H


