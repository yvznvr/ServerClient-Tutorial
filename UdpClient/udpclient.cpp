#include "udpclient.h"

UdpClient::UdpClient()
{

}

bool UdpClient::createSocket()
{
    socketCreated = true;

    // Creating socket file descriptor
    if ( (socketFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        socketCreated = false;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    // Filling server information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    return socketCreated;
}

bool UdpClient::isSocketCreated()
{
    return socketCreated;
}

uint8_t *UdpClient::sendData(uint8_t *data)
{
    bool messageSendOperationSuccess = false;
    uint8_t recievedData[5];
    socklen_t len = sizeof(serverAddr);

    while(!messageSendOperationSuccess)
    {
        sendto(socketFd, (const char *)data, 320,
                MSG_CONFIRM, (const struct sockaddr *) &serverAddr,
                sizeof(serverAddr));

        recvfrom(socketFd, (char *)recievedData, 6,
                        MSG_WAITALL, ( struct sockaddr *) &serverAddr,
                        &len);
        if(recievedData[0] == 0 && recievedData[1] == 0 && recievedData[2] == 0 &&
                recievedData[3] == 0 && recievedData[4] == 0 && recievedData[5] == 0)
        {
            messageSendOperationSuccess = true;
        }
    }

}

int UdpClient::getPort() const
{
    return port;
}

void UdpClient::setPort(int value)
{
    port = value;
}
