#include "qsavehelper.h"


/*
 * Default Konstruktor
 * Erstellt den QSaveHelper mit Defaultwerten damit dieser einfach von QBackupManager befüllt werden kann und
 * für die Backup Routine genutzt werden kann
 */
QSaveHelper::QSaveHelper()
{
    // Default-Werte
    this->destination   = QString();
    this->saveType      = QString();
    this->dir           = QDirNode();
}


/*
 * Fügt ein Element dem QSaveHelper hinzu; node ist eine Ordnerstruktur;
 * SaveType gibt an wie diese Struktur gespeichert werden soll
 * destination gibt an WO das Element gespeichert werdn soll
 */
void QSaveHelper::add(QDirNode node, QString saveType, QString destination, QString dBoxKey)
{
    // Elemente werden in Variablen gespeichert durch den Left Shift Operator (sozusagen ins Objekt geschoben)
    this->dir           = node;
    this->saveType      = saveType;
    this->destination   = destination;
    this->dBoxKey       = dBoxKey;
}


// Gibt das QDirNode zurück, welches auf dem derzeitigen Index des QSaveHelpers gespeichert ist. (Z.B.: Index 3 => QDirNode Objekt 3)
QDirNode QSaveHelper::getQDirNode() { return this->dir; }

// Gibt den SaveType zurück, welches auf dem derzeitigen Index des QSaveHelpers gespeichert ist.
QString QSaveHelper::getSaveType() { return this->saveType; }

// Gibt den Zielort für das Backupzurück, welches auf dem derzeitigen Index des QSaveHelpers gespeichert ist.
QString QSaveHelper::getDestination() { return this->destination; }

QString QSaveHelper::getDboxKey() { return this->dBoxKey; }
