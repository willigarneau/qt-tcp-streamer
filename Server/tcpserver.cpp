#include "tcpserver.h"

TCPServer::TCPServer()
{
    listen(QHostAddress::Any, 5555);
}

void TCPServer::incomingConnection(qintptr socket){
    TCPThread *thread = new TCPThread(socket);
    connect(thread, SIGNAL(Disconnect()), this, SLOT(on_thread_close()));
    connect(this, SIGNAL(newImg(QByteArray)), thread, SLOT(on_newImg(QByteArray)));
    thread->start();
    emit Connect();
}

void TCPServer::on_thread_close()
{
    emit Disconnect();
}

void TCPServer::is_newImg(QByteArray img){
    emit newImg(img);
}
