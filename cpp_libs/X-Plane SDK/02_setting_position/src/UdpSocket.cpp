#include <UdpSocket.h>

#include <cstring>
#include <iostream>

#ifdef __linux__
#   include <errno.h>
#   include <fcntl.h>
#   include <netdb.h>
#   include <sys/ioctl.h>
#endif // __linux__

UdpSocket::UdpSocket()
{
    memset(&_address, 0, sizeof(_address));

#   ifdef _WIN32
    WSADATA wsaData;
    if ( WSAStartup(MAKEWORD(2, 2), &wsaData) != 0 )
    {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        throw std::runtime_error("WSAStartup failed");
    }
#   endif // _WIN32

    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ( _socket == INVALID_SOCKET )
    {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        throw std::runtime_error("Socket creation failed");
    }

#   ifdef _WIN32
    WSACleanup();
#   endif // _WIN32
}

UdpSocket::~UdpSocket()
{
    close();
}

bool UdpSocket::bind(const std::string& address, uint16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if ( address.empty() || address == "0.0.0.0" )
    {
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        addr.sin_addr.s_addr = inet_addr(address.c_str());
        if ( addr.sin_addr.s_addr == INADDR_NONE )
        {
            std::cerr << "Invalid address: " << address << std::endl;
            return false;
        }
    }

    if ( ::bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR )
    {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        return false;
    }

    _address = addr;
    _bound = true;
    return true;
}

bool UdpSocket::connect(const std::string& address, uint16_t port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(address.c_str());

    if ( addr.sin_addr.s_addr == INADDR_NONE )
    {
        struct hostent* host = gethostbyname(address.c_str());
        if ( host == nullptr )
        {
            return false;
        }
        addr.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(host->h_addr);
    }

    int result = ::connect(_socket, (struct sockaddr*)&addr, sizeof(addr));
    if ( result != 0 )
    {
        std::cerr << "Connect failed: " << strerror(errno) << std::endl;
        return false;
    }

    _connected = true;
    return true;
}

bool UdpSocket::setNonBlocking(bool non_blocking)
{
#   ifdef _WIN32
    u_long mode = non_blocking ? 1 : 0;
    return ioctlsocket(_socket, FIONBIO, &mode) == 0;
#   endif // _WIN32

#   ifdef __linux__
    int flags = fcntl(_socket, F_GETFL, 0);
    if (flags < 0) return false;

    flags = non_blocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    return fcntl(_socket, F_SETFL, flags) == 0;
#   endif // __linux__
}

bool UdpSocket::hasPendingDatagrams() const
{
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(_socket, &read_set);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    return select(_socket + 1, &read_set, nullptr, nullptr, &timeout) > 0;
}

int UdpSocket::recv(char* buffer, int bufferSize)
{
    if ( !_bound )
    {
        return SOCKET_ERROR;
    }

    int bytes_received = ::recv(_socket, buffer, bufferSize, 0);
    if ( bytes_received < 0 )
    {
        std::cerr << "Receive failed: " << strerror(errno) << std::endl;
        return SOCKET_ERROR;
    }

    return bytes_received;
}

int UdpSocket::send(const char* buffer, int bufferSize)
{
    if ( !_connected )
    {
        return SOCKET_ERROR;
    }

    return ::send(_socket, buffer, bufferSize, 0);
}

int UdpSocket::sendto(const char* buffer, int bufferSize, const std::string& address, unsigned short port)
{
    if ( !_connected )
    {
        return SOCKET_ERROR;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(address.c_str());

    if (addr.sin_addr.s_addr == INADDR_NONE)
    {
        struct hostent* host = gethostbyname(address.c_str());
        if ( host == nullptr )
        {
            return SOCKET_ERROR;
        }
        addr.sin_addr.s_addr = *reinterpret_cast<unsigned long*>(host->h_addr);
    }

    return ::sendto(_socket, buffer, bufferSize, 0, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
}

void UdpSocket::close()
{
    if ( _socket != INVALID_SOCKET )
    {
#       ifdef _WIN32
        closesocket(_socket);
#       endif // _WIN32

#       ifdef __linux__
        ::close(_socket);
#       endif // __linux__
    }
    _socket = INVALID_SOCKET;
    _connected = false;
}