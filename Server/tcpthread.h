#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>

class TCPThread : public QThread
{
    Q_OBJECT
public:
    TCPThread(int nsocket);
signals:
    void Disconnect();
public slots:
    void on_newImg(QByteArray img);
private:
    QTcpSocket * socket;
    char nbClient;
};

#endif // TCPTHREAD_H
