#include <QCoreApplication>
#include "myserver.h"
#include "communicator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray auth_response;
    Communicator mycomm;

    bool authenticated = mycomm.authenticate(QString("testuser1"), QString("testpassword1"), &auth_response);

    qDebug() << QString("authenticated: ") << authenticated;
    qDebug() << QString("auth_response: ").append(auth_response);


    if (auth_response == QByteArray("authentication successful")) //wenn authentifizierung beim server erfolgreich war -> auf message von server warten
    {
        MyServer mServer; //client startet "seinen eigenen server" um zu lauschen
    }


    return a.exec();
}
