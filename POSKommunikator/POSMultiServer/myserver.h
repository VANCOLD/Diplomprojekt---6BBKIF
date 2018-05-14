#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "mythread.h"


class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void setobject(someotherclass *someobject);
    void setinputthread(InputThread *ithread);
    void StartServer();
    virtual ~MyServer();

    //QVector<MyThread*> threadlist;
    //void senduserstring(int userint, QString userstring);

signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);

private:
        someotherclass *someobject;
        InputThread *ithread;
};

#endif // MYSERVER_H
