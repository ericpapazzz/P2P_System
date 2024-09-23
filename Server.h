#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Enlazar con la biblioteca Winsock

class Server
{
public:
    SOCKET server_socket;
    struct sockaddr_in server_address;

    // Constructor del servidor
    Server(int domain, int service, int protocol, unsigned long interface_addr, int port, int backlog);

    // Destructor
    ~Server();
};

#endif // SERVER_H