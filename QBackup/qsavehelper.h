#ifndef QSAVEHELPER_H
#define QSAVEHELPER_H
#include <qdirnode.h>
#include <QList>
#include <QStringList>

class QSaveHelper
{

public:

    // Default Konstruktor; Wird genutzt um das Objekt zu instanzieren
    QSaveHelper();

    // Gibt das dezeitige getQDirNode des Objekts zurück (in Bezug auf derzeitigen Index)
    QDirNode getQDirNode();

    // Gibt das dezeitige SaveType (Speicherart) des Objekts zurück (in Bezug auf derzeitigen Index)
    QString getSaveType();

    // Gibt die derzeitige Destination (Zielort) des Objekts zurück (in Bezug auf derzeitigen Index)
    QString getDestination();

    // Fügt einen Record dem QSaveHelper hinzu; Wird für Dropbox genutzt; überladene Funktion
    void add(QDirNode node, QString saveType,QString destination, QString key);

    QString getDboxKey();


private:

    // Speichert die QDirNodes welche aus dem JSON File ausgelesen wurden.
    QDirNode dir;

    // Speichert die Backupvariante zugehörig zu einem QDirNode, welches aus dem JSON File ausgelesen wurden.
    QString saveType;

    // Speichert der Zielort des Backups zugehörig zu einem QDirNode, welche aus einem JSON File ausgelesen wurden.
    QString destination;

    QString dBoxKey = "";

};

#endif // QSAVEHELPER_H
