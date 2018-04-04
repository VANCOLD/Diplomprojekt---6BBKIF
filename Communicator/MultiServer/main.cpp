#include <QCoreApplication>
#include "myserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    someotherclass someobject;
    MyServer Server;
    Server.setobject(&someobject);
    Server.StartServer();

    return a.exec();
}
