#include "inputthread.h"
#include <iostream>
#include <string>

QString getustring(QString displaystring)
{
    std::string stdstring;
    std::cout << displaystring.toStdString();
    std::getline (std::cin,stdstring);
    return QString::fromUtf8(stdstring.c_str());
}

InputThread::InputThread(QObject *parent) : QThread(parent)
{

}
/*
void InputThread::setserver(MyServer *server)
{
    this->server = server;
}
*/
void InputThread::run()
{
    QString userstring = "";
    int userint = 1;

    while (userint != 0)
    {
        userint = getustring(QString("bitte nummer des clients eingeben: ")).toInt();
        userstring = getustring(QString("bitte nachricht eingeben: "));
        //this->server->senduserstring(userint, userstring);
        emit gotinput(userint, userstring);

    }
}
