#ifndef SOMEOTHERCLASS_H
#define SOMEOTHERCLASS_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QHostAddress>
//#include <QTest>

class someotherclass : public QObject
{
    Q_OBJECT
public:
    explicit someotherclass(QObject *parent = 0);

    QTcpSocket *socket;
    QJsonObject json;

signals:

public slots:

    void wait_and_send(int clientport);
    void sendtoclient(int clientport, QString userstring); //hier weiter. vlt als slot von inputthread aufrufen lassen
};

#endif // SOMEOTHERCLASS_H
