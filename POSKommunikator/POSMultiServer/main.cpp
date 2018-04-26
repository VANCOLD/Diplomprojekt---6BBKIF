#include <QCoreApplication>
#include "myserver.h"
#include <iostream>
#include <string>

QString getustring(QString displaystring)
{
    std::string stdstring;
    std::cout << displaystring.toStdString();
    std::getline (std::cin,stdstring);
    return QString::fromUtf8(stdstring.c_str());
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    someotherclass someobject;
    MyServer Server;
    Server.setobject(&someobject);
    Server.StartServer();



    /*
    QString userstring = "";
    int userint = 1;

    while (userint != 0)
    {
        userint = getustring(QString("bitte nummer des clients eingeben: ")).toInt();
        userstring = getustring(QString("bitte nachricht eingeben :"));
        Server.senduserstring(userint, userstring);
    }*/



    return a.exec();
}
