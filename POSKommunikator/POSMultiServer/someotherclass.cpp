#include "someotherclass.h"

someotherclass::someotherclass(QObject *parent) : QObject(parent)
{

}

void someotherclass::sendtoclient(int clientport, QString userstring)
{
    this->socket = new QTcpSocket(this);

    this->socket->connectToHost(QHostAddress::LocalHost, clientport);

    if(socket->waitForConnected(5000))
    {
        qDebug() << "sendtoclient connected!";

        json.insert("type", QJsonValue("usermsg"));
        json.insert("usermsg", QJsonValue(userstring));

        this->socket->write(QJsonDocument(json).toJson());

        this->socket->waitForBytesWritten(1000);

        qDebug() << "usermsgJSon sent";
    }
    else
    {
        qDebug() << "sendtoclient couldn't connect!";
    }

}


void someotherclass::wait_and_send(int clientport)
{
    //QTest::qWait(1000);



    /*

    this->socket = new QTcpSocket(this);

    this->socket->connectToHost(QHostAddress::LocalHost, clientport);

    if(socket->waitForConnected(5000))
    {
        qDebug() << "waitandsend Connected!";

        json.insert("type", QJsonValue("debug"));

        this->socket->write(QJsonDocument(json).toJson());

        this->socket->waitForBytesWritten(1000);

        qDebug() << "debugJSon sent";
    }
    else
    {
        qDebug() << "waitandsend Couldn't connect!";
    }


    */
}
