#include <QCoreApplication>
#include <QTimer>
#include <qbackupmanager.h>
#include <qlogger.h>
// #include <qcommunicator.h>

QLogger l = QLogger();

int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);


    // QCommunicator *clientCom    = new QCommunicator();
    QBackupManager* manager  = new QBackupManager();
    qDebug() << "Starte Programm\n";

    manager->init();
    qDebug() << "Starte Backup-Routine\n";
    manager->initBackup();

    delete manager;
    return a.exec();
}
