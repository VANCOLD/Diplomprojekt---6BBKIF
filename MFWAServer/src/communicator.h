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

    bool authenticate(QString username, QString password, QByteArray *response_data);

signals:

public slots:
};

#endif // COMMUNICATOR_H
