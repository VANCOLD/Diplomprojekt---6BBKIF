#include "mythread.h"


MyThread::MyThread(int ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    //thread starts here
    qDebug() << socketDescriptor << "Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << "Client connected";

    exec();
}

void MyThread::readyRead()
{
    QByteArray Data = socket->readAll();
    qDebug() << socketDescriptor << "Data in: " << Data;

    QJsonDocument jsondoc = QJsonDocument::fromJson(Data);
    QJsonObject jsonobj = jsondoc.object();

    if (jsonobj.contains(QString("type")))
    {
        if (jsonobj.value(QString("type")) == QJsonValue("authentication"))
        {
            if (jsonobj.value(QString("username")) == QJsonValue("testuser1"))
            {
                if (jsonobj.value(QString("password")) == QJsonValue("testpassword1"))
                {
                    socket->write("authentication successful");

                   emit signaltowaitandsend();
                   qDebug("signaltowaitandsend emitted");
                }
                else socket->write("wrong password");
            }
            else socket->write("unknown user");
        }
        else socket->write("Warning: Received JSon of unknown type");
    }
    else socket->write("Warning: Received JSon without \"type\" key");
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    socket->deleteLater();
    exit(0);
}
