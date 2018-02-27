#include "communicator.h"

Communicator::Communicator(QObject *parent) : QObject(parent)
{


}

bool Communicator::authenticate(QString username, QString password, QByteArray *response_data)
{
     request = QNetworkRequest(QUrl("http://localhost:8080/json"));
     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

     json.insert("type", QJsonValue("authentication"));
     json.insert("username", QJsonValue(username));
     json.insert("password", QJsonValue(password));

     reply = nam.post(request, QJsonDocument(json).toJson());
     qDebug() << "JSON geschickt";

     while(!reply->isFinished())
     {
         qApp->processEvents();
     }
     qDebug() << "Antwort erhalten";

     *response_data = reply->readAll();
  //   qDebug() << QString("").append(*response_data);
     qDebug() << "Fertig!";

     if (*response_data == "authentication successful")
     return 1;
     else
     return 0;
}
