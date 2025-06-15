#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <string>

#ifdef WIN32
#   include <winsock2.h>
#   include <ws2tcpip.h>
#endif // WIN32

#ifdef __linux__
#   include <unistd.h>
#   include <arpa/inet.h>
#   include <sys/socket.h>
#endif // __linux__

class UdpSocket
{
public:

#   ifdef __linux__
    using SOCKET = int;
    constexpr static int INVALID_SOCKET = -1;
    constexpr static int SOCKET_ERROR = -1;
#   endif // __linux__

    UdpSocket();

    ~UdpSocket();

    bool bind(const std::string& address, uint16_t port);

    bool connect(const std::string& address, uint16_t port);

    bool setNonBlocking(bool non_blocking);

    bool hasPendingDatagrams() const;

    int recv(char* buffer, int bufferSize);

    int send(const char* buffer, int bufferSize);

    int sendto(const char* buffer, int bufferSize, const std::string& address, unsigned short port);

private:

    SOCKET _socket = INVALID_SOCKET;
    struct sockaddr_in _address;
    bool _bound = false;
    bool _connected = false;

    void close();
};

#endif // UDPSOCKET_H
