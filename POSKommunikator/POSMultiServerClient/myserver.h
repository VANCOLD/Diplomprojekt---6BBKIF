#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0, int port = 12345);

signals:

public slots:
    void newConnection();

private:
    QTcpServer *server;
    int port;
};

#endif // MYSERVER_H
