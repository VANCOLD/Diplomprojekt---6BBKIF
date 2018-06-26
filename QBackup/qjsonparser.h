#ifndef QJSONPARSER_H
#define QJSONPARSER_H
#include <QString>
#include <QStringList>
#include <QXmlStreamReader>
#include <QFileInfo>
#include <qdebug.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class QJsonParser
{


public:

    //*** Konstruktoren ***//

        // Hauptkonstruktor. Liest die Daten eines <dir> Tags aus und speichert sie in den Objekt-Instanzvariablen
        QJsonParser(QString content, QString JsonPath);

        // Default-Kontruktor
        QJsonParser();

    //*** ENDE Konstruktoren ***//



    //*** GETTER-FUNKTIONEN ***//

        // Gibt den Pfad des Auftrages zurück, falls dieses lokal vorhanden ist wird ein Pfad zurück gegeben,
        // Ansonsten ist der Strin leer.
        QString getJsonPath();

        // Gibt den Ordner-Pfad zurück, des eingelesenen <dPath> tags
        QString getDirPath();

        // Gibt die gültigen Filter zurück, des eingelesenen <filter> tags
        QStringList getFilters();

        // Gibt die exkludierten Ordner zurück, des eingelesenen <excluded> tags
        QStringList getExcludedDirs();

        // Gibt an ob die eingelesen Ordner-Daten gültig sind (true: gültig; false: ungültig)
        bool isValid();

        // Gibt den ausgelesenen Wert für type im XML File aus
        QString getDest();

        // Gibt den saveType zurück welcher im XML File spezifiziert wurde
        // Möglich sind: local, gdrive (Google Drive) und dbox (Dropbox)
        QString getSaveType();

        // Gibt den vom User festgelegten Namen der Sicherungs-Aufgabe zurück
        QString getName();

        QString getDboxKey();

    //*** ENDE GETTER-FUNKTIONEN ***//

private:

    // Der vom User vergebene Name für die Sicherungs-Aufgabe
    QString name;

    // Pfad in dem der Json Auftrag gespeichert ist (falls dieser lokal vorhanden ist; Bei HTTP Auftrag ist dieses Feld leer)
    QString JsonPath;

    // Pfad eines Ordners, der für die Backup-Routine bestimmt ist
    QString path;

    // QStringList, welche die Dateiendungen speichert. Nach diesen Endungen werden im Ordner mit dem Pfad von path gesucht.
    QStringList filters;

    // QStringList, welche die Ordner beinhaltet, welche beim Backup vorgang übersprungen werden sollen.
    QStringList excluded;

    // Gibt an ob dieses QXmlParser Objekt gültig / nutzbare oder ungültige / nicht nutzbare Daten enthält.
    bool valid;

    // Ort an dem die Ordner-Struktur später gespeichert werden soll
    QString destination;

    // Art wie das Backup stattfinden soll
    QString saveType;

    QString dBoxKey;

};

#endif // QJSONPARSER_H
