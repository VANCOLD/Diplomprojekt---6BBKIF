#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "mythread.h"
#include "someotherclass.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void setobject(someotherclass *someobject);
    void StartServer();
    virtual ~MyServer();

signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);

private:
        someotherclass *someobject;
};

#endif // MYSERVER_H
