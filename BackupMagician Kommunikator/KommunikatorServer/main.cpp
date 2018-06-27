#include <QCoreApplication>
//#include "inputthread.h"
#include "myserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InputThread ithread;
    ithread.start();

    someotherclass someobject;

    QObject::connect(&ithread, SIGNAL(gotinput(int /*clientnumber*/, QString /*userstring*/)), &someobject, SLOT(sendtoclient(int /*clientnumber*/, QString /*userstring*/)));

    MyServer Server;
    Server.setobject(&someobject);
    Server.StartServer();

    return a.exec();
}
