#include <QCoreApplication>
#include "myserver.h"
#include "communicator.h"
#include "inputthread.h"
#include <iostream>
#include <string>
/*
QString getustring(QString displaystring)
{
    std::string stdstring;
    std::cout << displaystring.toStdString();
    std::getline (std::cin,stdstring);
    return QString::fromUtf8(stdstring.c_str());
}
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int port = getustring(QString("Please enter port to listen on: ")).toInt();

    QByteArray response;
    Communicator mycomm;
    InputThread ithread;

    mycomm.setport(port);

    MyServer * mServer = NULL;

    if (mycomm.connect()) //wenn verbindung aufgebaut werden konnte
    {
        bool authenticated = mycomm.authenticate(QString("testuser1"), QString("testpassword1"), &response);

        qDebug() << QString("authenticated: ") << authenticated;
        qDebug() << QString("response from server: ").append(response);

        if (response == QByteArray("authentication successful"))
        {
            mServer = new MyServer(NULL, port); //client startet "seinen eigenen server" um zu lauschen

            QObject::connect(&ithread, SIGNAL(gotinput(QString, QString, QString)), &mycomm, SLOT(senduserjsonslot(QString, QString, QString)));

            ithread.start();


/*          QString type = "";
            QString username = "";
            QString password = "";

            do
            {
                type = getustring(QString("Please enter \"reg\" or \"auth\" or \"quit\": "));
                if (type != "quit")
                {
                    username = getustring(QString ("Please enter username: "));
                    password = getustring(QString("Please enter password: "));

                    mycomm.senduserjson(type, username, password, &response);
                }
            } while (type != "quit"); */
        }
    }


    int ret = a.exec();
    delete mServer;
    return ret;
}
