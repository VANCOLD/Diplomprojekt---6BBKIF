#ifndef QBACKUPMANAGER_H
#define QBACKUPMANAGER_H

#include <QObject>
#include <QFile>
#include <qdirnode.h>
#include <qjsonparser.h>
#include <QList>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <qsavehelper.h>
#include <iostream>
#include <QMessageLogger>
#include <QThread>
#include <QJsonDocument>
#include <QException>

class QBackupManager : public QObject
{
    Q_OBJECT


public:

    // Verbung; Hier wird sichergestellt das QBackupManager ein Kind von QObject ist (wegen Signal und Slot)
    explicit QBackupManager(QObject *parent = 0): QObject(parent) { this->finished = false;}

    // Initialisiert die Ordnerstruktur
    void init();

    // Slot für das erstellen des Backups; Diese Funktion wird angesteuert wenn Tasks beim Client angekommen sind.
    void initBackup();



private:

    // finished speichert ob die Backup-Tasks abgearbeitet wurden
    bool finished;

    QJsonParser save;
    QDirNode    node;

    void gDriveSave();
    void dBoxSave();
    void iCloudSave();


    // JSON Parser; Wird in zukunft mit einem JSON Parser ausgetauscht. List alle wichtige Informationen aus den Tasks (XML-Files aus)
    bool readJSON(QJsonParser &dirs);



};

#endif // QBACKUPMANAGER_H
