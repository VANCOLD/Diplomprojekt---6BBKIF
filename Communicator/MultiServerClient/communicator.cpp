#include "communicator.h"
#include <QHostAddress>

Communicator::Communicator(QObject *parent) : QObject(parent)
{


}

bool Communicator::authenticate(QString username, QString password, QByteArray *response_data)
{
     //request = QNetworkRequest(QUrl("http://localhost:8080/json"));
     //request = QNetworkRequest(QUrl("http://localhost:1234"));
     //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

     socket = new QTcpSocket(this);

     socket->connectToHost(QHostAddress::LocalHost, 1234);

     if(socket->waitForConnected(3000))
     {
         qDebug() << "Connected!";
     }
     else
     {
         qDebug() << "Couldn't connect!";
     }

     json.insert("type", QJsonValue("authentication"));
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

     if (*response_data == "authentication successful")
     return 1;
     else
     return 0;
}
