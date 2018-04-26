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

void MyServer::senduserstring(int userint, QString userstring)
{
    //QVector<MyThread*>::iterator i =
    foreach(MyThread* mt,this->threadlist)
    {
        if(mt->getsocketdescriptor() == userint) {
            QByteArray tempContent(userstring.toUtf8());
            mt->getQTcpSocket()->write(tempContent);
            mt->getQTcpSocket()->waitForBytesWritten(1000);

        }



    }

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
    //clientlist.contains(socketDescriptor) <----------------------------hier gehts weiter
    qDebug() << socketDescriptor << "Connecting...";
    MyThread *thread = new MyThread(socketDescriptor, this);
    threadlist.append(thread);
    connect (thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect (thread, SIGNAL(signaltowaitandsend(int)), this->someobject, SLOT(wait_and_send(int)));
    thread->start();


}
