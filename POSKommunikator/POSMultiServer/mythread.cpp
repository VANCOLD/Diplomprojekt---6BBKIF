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

    /*
    qDebug() << "before connecting gotinput to writesocket";
    connect(this->ithread, SIGNAL(gotinput(int, QString)), this, SLOT(writetosocket(int, QString)));
    qDebug() << "after connecting gotinput to writesocket";
    */

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << "Client connected";

    exec();
}

void MyThread::setinputthread(InputThread *ithread)
{
    this->ithread = ithread;
}

void MyThread::writetosocket(int clientnumber, QString userstring)
{
    if(this->socketDescriptor == clientnumber)
    {
        QByteArray tempContent(userstring.toUtf8());
        socket->write(tempContent);
        socket->waitForBytesWritten(1000);
    }
}
/*
int MyThread::getsocketdescriptor()
{
    return this->socketDescriptor;
}
*/
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

                   emit signaltowaitandsend(jsonobj.value(QString("clientport")).toInt());
                   qDebug("signaltowaitandsend emitted");
                }
                else socket->write("wrong password");
            }
            else socket->write("unknown user");
        }
        else if (jsonobj.value(QString("type")) == QJsonValue("userstring"))
        {
            socket->write("userstring successfully received");
            if (jsonobj.value(QString("userstring")) == QJsonValue("quit"))
            {
                this->disconnected();
            }
        }
        else socket->write("Warning: Received JSon of unknown type");
    }
    else socket->write("Warning: Received JSon without \"type\" key");
}
/*
QTcpSocket* MyThread::getQTcpSocket() {
    return this->socket;
}
*/

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    socket->deleteLater();
    exit(0);
}
