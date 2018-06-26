#include <qlogger.h>


// Wird nur benötigt um das File zu öffnen und den MessageHandler zu starten (Das File wird hier zum ersten mal geöffnet)
QLogger::QLogger()
{
    if(!QDir(QFileInfo(outFile).path()).exists())
        QDir().mkdir(QFileInfo(outFile).path());

        outFile.open(QIODevice::Append | QIODevice::ReadWrite | QIODevice::Text);
        qInstallMessageHandler(myMessageHandler); // Linkt meine myMessageHandler Funktion mit dem allgemeinen MessageHandler (qDebug,qError etc)
}


// Wird hier nur angeführt zwecks Vollständigkeit.
QLogger::~QLogger() {}
