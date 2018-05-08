#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "someotherclass.h"
#include "inputthread.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(int ID, QObject *parent = 0);
    void run();
//  int getsocketdescriptor();
//  QTcpSocket* getQTcpSocket();
    void setinputthread(InputThread *ithread);

signals:
    void error(QTcpSocket::SocketError socketerror);
    void signaltowaitandsend(int clientport);

public slots:
    void readyRead();
    void disconnected();
    void writetosocket(int clientnumber, QString userstring);

public slots:

private:
    QTcpSocket *socket;
    int socketDescriptor;
    InputThread *ithread;

};

#endif // MYTHREAD_H
