#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <iostream>

#ifdef WIN32
    #include <Winsock.h>
    #include <windows.h>
#endif

#ifdef _LINUX_
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <string.h>
#endif

class UdpSocket
{
public:

    UdpSocket()
    {
#       ifdef WIN32
        int retval = -1;
        if ((retval = WSAStartup(0x202, &wsaData)) != 0)
        {
            std::cerr << "Error initializing WSA " << retval << std::endl;
            return;
        }

        if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET )
        {
            WSACleanup();
            std::cerr << "Error creating socket " << WSAGetLastError() << std::endl;
            return;
        }
#       endif // WIN32

#       ifdef _LINUX_
        if ( (_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 )
        {
            std::cerr << "Error creating socket" << std::endl;
            return;
        }
#       endif // _LINUX_
    }

    ~UdpSocket()
    {
#       ifdef WIN32
        closesocket(_sock);
#       endif
    }

    void bind(const char* ip, int port)
    {
        memset(&_local, 0, sizeof(_local));
        _local.sin_family = AF_INET;
        _local.sin_port = htons(port);
        _local.sin_addr.s_addr = inet_addr(ip);

#       ifdef WIN32
        if (bind(_sock, (struct sockaddr*)&_local, sizeof(_local)) == SOCKET_ERROR)
        {
            std::cerr << "Error binding socket " << WSAGetLastError() << std::endl;
            return;
        }
#       endif // WIN32

#       ifdef _LINUX_
        ::bind(_sock,  (struct sockaddr*)(&_local), sizeof(_local) );
#       endif
    }

    void connect(const char* ip, int port)
    {
        memset(&_remote, 0, sizeof(_remote));
        _remote.sin_family = AF_INET;
        _remote.sin_port = htons(port);
        _remote.sin_addr.s_addr = inet_addr(ip);

#       ifdef WIN32
        if (::connect(sock, (struct sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR)
        {
            WSACleanup();
            std::cerr << "[  ERROR  ] MSc_Sock: Connecting failed with error: " << WSAGetLastError() << std::endl;
        }
#       endif // WIN32
    }

    bool isPending()
    {
        struct timeval timeout;
        fd_set socketSet;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1;
        FD_ZERO(&socketSet);
        FD_SET(_sock, &socketSet);
        if (select(0,&socketSet,0,0,&timeout) != 0)
        {
            return true;
        }

        return false;
    }

    void send(const char* data, int size, const char* ip, int port)
    {
        int sent_bytes = -1;

#       ifdef WIN32
        sent_bytes = ::send(_sock, data, size, 0);
#       endif

#       ifdef _LINUX_
        struct sockaddr_in remote;

        memset(&remote, 0, sizeof(remote));
        remote.sin_family = AF_INET;
        remote.sin_addr.s_addr = inet_addr(ip);
        remote.sin_port = htons(port);
        sent_bytes = sendto(_sock, data, size, 0, (struct sockaddr*)(&_remote), sizeof(_remote));
#       endif

        if ( sent_bytes != (int)size )
        {
            std::cerr << "Error sending data " << sent_bytes << std::endl;
        }
    }

    void receive(char* data, int size)
    {
        int remotelen = sizeof(_remote);

#       ifdef WIN32
        int retval = recvfrom(_sock, data, size, 0, (struct sockaddr*)(&_from), &remotelen);
        if (retval == SOCKET_ERROR)
        {
            std::cerr << "Error receiving data " << WSAGetLastError() << std::endl;
        }
        else if (retval == 0)
        {
            std::cerr << "Connection closed" << std::endl;
        }
#       endif

#       ifdef _LINUX_
        //int retval = recvfrom(sock, data, max_size, 0, (struct sockaddr *)(&from), (socklen_t*)(&remotelen));
        recvfrom(_sock, data, size, 0, (struct sockaddr *)(&_from), (socklen_t*)(&remotelen));
#       endif
    }

private:

    struct sockaddr_in _local;
    struct sockaddr_in _remote;
    struct sockaddr_in _from;

#   ifdef WIN32
    SOCKET _sock;
    WSADATA _wsaData;
#   endif

#   ifdef _LINUX_
    int _sock;
#   endif
};

#endif // UDPSOCKET_H
