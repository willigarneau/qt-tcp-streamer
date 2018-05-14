#ifndef TCPSERVER_H
#define TCPSERVER_H
// Added library for TCP Server
#include <QTcpServer>
// Added library for TCP Socket
#include <QTcpSocket>
// Access tcp thread
#include "tcpthread.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    TCPServer();
    void is_newImg(QByteArray img);
signals:
    void newImg(QByteArray img);
    void Connect();
    void Disconnect();
public slots:
    void on_thread_close();
private:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // TCPSERVER_H
