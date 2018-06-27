#include "myserver.h"

MyServer::MyServer(QObject *parent) : QTcpServer(parent)
{

}

void MyServer::setobject(someotherclass *someobject)
{
    this->someobject = someobject;
}

MyServer::~MyServer()
{
    delete this->someobject;
}

void MyServer::StartServer()
{
    if(!this->listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void MyServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << "Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, this);

    connect (thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect (thread, SIGNAL(signaltowaitandsend(int)), this->someobject, SLOT(wait_and_send(int)));

    thread->start();
}
