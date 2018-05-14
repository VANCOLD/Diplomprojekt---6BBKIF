#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include <QtNetwork>
#include <QUrl>
#include <QDebug>

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = 0);

    QNetworkAccessManager nam;
    QNetworkRequest request;
    QJsonObject json;
    QNetworkReply *reply;

    QTcpSocket *socket;

    int port;

    void setport(int port);
    bool connect();
    bool authenticate(QString username, QString password, QByteArray *response_data);
    bool senduserstring(QString userstring, QByteArray *response_data);
    bool senduserjson(QString type, QString username, QString password, QByteArray *response_data);

signals:

public slots:
};

#endif // COMMUNICATOR_H
