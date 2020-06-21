#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


class UdpClient
{
public:
    UdpClient();
    bool createSocket();
    // isSocketCreated() returns true if socket created
    // otherwise returns false
    bool isSocketCreated();
    uint8_t* sendData(uint8_t *data);
    int getPort() const;
    void setPort(int value);

private:
    int socketFd;
    bool socketCreated = false;
    // 320 bytes max data payload of UDP Protocol
    uint8_t buffer[320];
    struct sockaddr_in serverAddr;
    int port;
};

#endif // UDPCLIENT_H
