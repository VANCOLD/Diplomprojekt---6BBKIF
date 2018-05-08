#include <QCoreApplication>
//#include "inputthread.h"
#include "myserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InputThread ithread;
    ithread.start();

    someotherclass someobject;
    MyServer Server;
    Server.setobject(&someobject);
    Server.setinputthread(&ithread);
    Server.StartServer();

/*
    InputThread ithread;
    ithread.setserver(&Server);
    ithread.start();
*/
    /*
    QString userstring = "";
    int userint = 1;

    while (userint != 0)
    {
        userint = getustring(QString("bitte nummer des clients eingeben: ")).toInt();
        userstring = getustring(QString("bitte nachricht eingeben :"));
        Server.senduserstring(userint, userstring);
    }
    */



    return a.exec();
}
