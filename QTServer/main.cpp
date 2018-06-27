#include <QApplication>
#include "myserver.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    InputThread ithread;
    ithread.start();

    someotherclass someobject;
    MyServer Server;
    Server.setobject(&someobject);
    Server.setinputthread(&ithread);
    Server.StartServer();



    return a.exec();
}
