#ifndef UDPSERVER_H
#define UDPSERVER_H

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <QThread>

class UdpServer: public QThread
{
    Q_OBJECT
public:
    explicit UdpServer();
    bool createSocket();
    // isSocketCreated() returns true if socket created
    // otherwise returns false
    bool isSocketCreated();
    uint8_t* recieveData();
    void sendData(uint8_t *data);
    int getPort() const;
    void setPort(int value);
    void run();

private:
    int socketFd;
    bool socketCreated = false;
    // 320 bytes max data payload of UDP Protocol
    uint8_t buffer[320];
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int port;
signals:
    void recvData(uint8_t*);
};

#endif // UDPSERVER_H
