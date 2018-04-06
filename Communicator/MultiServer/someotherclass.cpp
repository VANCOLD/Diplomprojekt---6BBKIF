#include "someotherclass.h"

someotherclass::someotherclass(QObject *parent) : QObject(parent)
{

}

void someotherclass::wait_and_send()
{
    //QTest::qWait(1000);

    this->socket = new QTcpSocket(this);

    this->socket->connectToHost(QHostAddress::LocalHost, 10235);

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

}
