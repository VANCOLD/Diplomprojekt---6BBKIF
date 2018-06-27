#include "inputthread.h"
#include <iostream>
#include <string>
#include <QDebug>

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

void InputThread::run()
{
    QString userstring = "";
    int port = 1;

    while (port != 0)
    {
        port = getustring(QString("bitte port des clients eingeben: ")).toInt();
        userstring = getustring(QString("bitte nachricht eingeben: "));

        emit gotinput(port, userstring);
    }
}
