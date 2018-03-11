#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>
#include "httplistener.h"
#include "httprequesthandler.h"
#include "requestmapper.h"
#include "communicator.h"

/**
 * Search the configuration file.
 * Aborts the application if not found.
 * @return The valid filename
 */
QString searchConfigFile() {
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QFile file;
    file.setFileName(binDir+"/webapp1.ini");
    if (!file.exists()) {
        file.setFileName(binDir+"/etc/webapp1.ini");
        if (!file.exists()) {
            file.setFileName(binDir+"/../etc/webapp1.ini");
            if (!file.exists()) {
                file.setFileName(binDir+"/../"+appName+"/etc/webapp1.ini");
                if (!file.exists()) {
                    file.setFileName(binDir+"/../../"+appName+"/etc/webapp1.ini");
                    if (!file.exists()) {
                        file.setFileName(binDir+"/../../../../../"+appName+"/etc/webapp1.ini");
                        if (!file.exists()) {
                            file.setFileName(QDir::rootPath()+"etc/webapp1.ini");
                        }
                    }
                }
            }
        }
    }
    if (file.exists()) {
        QString configFileName=QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    }
    else {
        qFatal("config file not found");
    }
}

using namespace stefanfrings;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    /*
    QByteArray auth_response;
    Communicator mycomm;

    bool authenticated = mycomm.authenticate(QString("testuser1"), QString("testpassword1"), &auth_response);

    qDebug() << QString("authenticated: ") << authenticated;
    qDebug() << QString("auth_response: ").append(auth_response);
    */


    // Load the configuration file
    QString configFileName=searchConfigFile();
    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &app);
    qDebug("config file loaded");
    listenerSettings->beginGroup("listener");

    HttpListener* myListener = new HttpListener(listenerSettings, new RequestMapper(&app,myListener), &app);

    Communicator mycomm;

    qDebug("mycomm created");

    QObject::connect(myListener, SIGNAL(signaltowaitandsend()), &mycomm, SLOT(wait_and_send()));

    qDebug("connected slot to signal");

    return app.exec();
}
