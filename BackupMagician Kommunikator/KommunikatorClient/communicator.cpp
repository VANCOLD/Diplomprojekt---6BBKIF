#include "communicator.h"
#include <QHostAddress>

#define CLIENTPORT 12345
Communicator::Communicator(QObject *parent) : QObject(parent)
{


}

void Communicator::setport(int port)
{
    this->port = port;
}

bool Communicator::connect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost(QHostAddress::LocalHost, 1234);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        return true;
    }
    else
    {
        qDebug() << "Couldn't connect!";
        return false;
    }

}

void Communicator::senduserjsonslot(QString type, QString username, QString password)
{
    json.insert("type", QJsonValue(type));
    json.insert("username", QJsonValue(username));
    json.insert("password", QJsonValue(password));

    socket->write(QJsonDocument(json).toJson());

    socket->waitForBytesWritten(1000);
    qDebug() << "JSON geschickt";
}

bool Communicator::senduserjson(QString type, QString username, QString password, QByteArray *response_data)
{
     //request = QNetworkRequest(QUrl("http://localhost:8080/json"));
     //request = QNetworkRequest(QUrl("http://localhost:1234"));
     //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

     json.insert("type", QJsonValue(type));
     //json.insert("ID",QJsonValue("1"));
     json.insert("username", QJsonValue(username));
     json.insert("password", QJsonValue(password));

     socket->write(QJsonDocument(json).toJson());

     socket->waitForBytesWritten(1000);

     qDebug() << "JSON geschickt";

     socket->waitForReadyRead(3000);

     qDebug() << "Antwort erhalten";

     *response_data = socket->readAll();
  //   qDebug() << QString("").append(*response_data);
     qDebug() << "Fertig!";

     if (*response_data == "userstring successfully received")
     return 1;
     else
     return 0;
}

bool Communicator::senduserstring(QString userstring, QByteArray *response_data)
{
     //request = QNetworkRequest(QUrl("http://localhost:8080/json"));
     //request = QNetworkRequest(QUrl("http://localhost:1234"));
     //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

     json.insert("type", QJsonValue("userstring"));
     json.insert("ID",QJsonValue("1"));
     json.insert("userstring", QJsonValue(userstring));
     json.insert("clientport", QJsonValue(this->port));
     socket->write(QJsonDocument(json).toJson());

     socket->waitForBytesWritten(1000);

     qDebug() << "JSON geschickt";

     socket->waitForReadyRead(3000);

     qDebug() << "Antwort erhalten";

     *response_data = socket->readAll();
  //   qDebug() << QString("").append(*response_data);
     qDebug() << "Fertig!";

     if (*response_data == "userstring successfully received")
     return 1;
     else
     return 0;
}

bool Communicator::authenticate(QString username, QString password, QByteArray *response_data)
{
     //request = QNetworkRequest(QUrl("http://localhost:8080/json"));
     //request = QNetworkRequest(QUrl("http://localhost:1234"));
     //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

     json.insert("type", QJsonValue("authentication"));
     json.insert("username", QJsonValue(username));
     json.insert("password", QJsonValue(password));
     json.insert("clientport", QJsonValue(this->port));

     socket->write(QJsonDocument(json).toJson());

     socket->waitForBytesWritten(1000);

     qDebug() << "JSON geschickt";

     socket->waitForReadyRead(3000);

     qDebug() << "Antwort erhalten";

     *response_data = socket->readAll();
  //   qDebug() << QString("").append(*response_data);
     qDebug() << "Fertig!";

     if (*response_data == "authentication successful")
     return 1;
     else
     return 0;
}
