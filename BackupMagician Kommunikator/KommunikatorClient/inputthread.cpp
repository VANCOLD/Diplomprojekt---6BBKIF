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
    QString type = "";
    QString username = "";
    QString password = "";

    do
    {
        type = getustring(QString("Please enter \"reg\" or \"auth\" or \"quit\": "));
        if (type != "quit")
        {
            username = getustring(QString ("Please enter username: "));
            password = getustring(QString("Please enter password: "));

         // mycomm.senduserjson(type, username, password);
            emit gotinput(type, username, password);
        }
    } while (type != "quit");
}
