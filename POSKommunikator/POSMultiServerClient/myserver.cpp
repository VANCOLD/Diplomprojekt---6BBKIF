#include "myserver.h"

#define CLIENTPORT 12345

MyServer::MyServer(QObject *parent, int port) : QObject(parent)
{
    this->port = port;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void MyServer::newConnection()
{

    qDebug() << "connection accepted";

    QTcpSocket *socket = server->nextPendingConnection();

    socket->waitForReadyRead(3000);

    qDebug() << socket->readAll();


    socket->close();
}
