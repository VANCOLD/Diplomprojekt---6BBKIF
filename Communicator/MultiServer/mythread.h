#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "someotherclass.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(int ID, QObject *parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void signaltowaitandsend();

public slots:
    void readyRead();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    int socketDescriptor;

};

#endif // MYTHREAD_H
