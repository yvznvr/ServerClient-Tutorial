#include "udpserver.h"

UdpServer::UdpServer()
{

}

bool UdpServer::createSocket()
{
    socketCreated = true;
    if ( (socketFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            socketCreated = false;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    // Filling server information
    serverAddr.sin_family    = AF_INET; // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    // Bind the socket with the server address
    if ( bind(socketFd, (const struct sockaddr *)&serverAddr,
            sizeof(serverAddr)) < 0 )
    {
        socketCreated = false;
    }

    return socketCreated;
}

bool UdpServer::isSocketCreated()
{
    return socketCreated;
}

uint8_t* UdpServer::recieveData()
{
    socklen_t len = sizeof(clientAddr);
    int dataSize = recvfrom(socketFd, (char *)buffer, 320,
                MSG_WAITALL, ( struct sockaddr *) &clientAddr,
                &len);
    buffer[dataSize] = '\0';
    emit recvData(buffer);
}

void UdpServer::sendData(uint8_t *data)
{
    sendto(socketFd, (const char *)data, 6,
            MSG_CONFIRM, (const struct sockaddr *) &clientAddr,
            sizeof(clientAddr));
}

int UdpServer::getPort() const
{
    return port;
}

void UdpServer::setPort(int value)
{
    port = value;
}

void UdpServer::run()
{
    if(socketCreated)
    {
        while(true)
        {
            recieveData();
        }
        this->msleep(1);
    }
}
