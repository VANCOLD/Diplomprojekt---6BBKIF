#include "myserver.h"

MyServer::MyServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 10235))
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
