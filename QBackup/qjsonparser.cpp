#include "qjsonparser.h"


/*
 * Hauptkonstruktor
 *
 * Dieser Konstruktor übernimmt ein QXmlStreamReader pointer, welcher zum Auslesen
 * der Tags im File genutzt wird.
 * Es gibt hier 3 Tags die wichtig sind, filter,excluded und dPath
 *
 * Diese werden gespeichert, falls das Objekt aber keine gültigen
 * Daten enthält wird es als invalid makiert. In diesem Fall würde
 * das Programm dieses Objekt verwerfen
 *
 */
QJsonParser::QJsonParser(QString content, QString JsonPath)
{

    // Deklarieren und initialisieren der Instanzvariablen (mit default-werten)
    this->path     = "";
    // Speichert welche Unterordner fürs Backup ignoriert werden sollen
    this->excluded = QStringList();
    // Speichert den Filter für Datenendung; => *.gif, *.jpg = Nur gifs und jpgs speichern
    this->filters  = QStringList();

    this->JsonPath = JsonPath;


    QJsonDocument doc   = QJsonDocument::fromJson(content.toUtf8());
    QJsonValue value = doc.object().value(QString("qdirnode"));
    QJsonObject item = value.toObject();

    this->path          = item["dPath"].toString();
    this->saveType      = item["saveType"].toString();
    this->destination   = item["dest"].toString();
    this->excluded      = item["excluded"].toString().split(";");
    this->filters       = item["filter"].toString().split(";");
    this->name          = item["name"].toString();

    qDebug() << this->saveType;
    if(this->saveType == "dbox")
        this->dBoxKey = item["dboxKey"].toString();

    /*
    // Solange der Endtag dir nicht kommt und kein Fehler auftritt soll die Schleife ausgeführt werden
    while((reader->name() != "dir") && !reader->hasError())
    {
        // Nächstes Element des XML-Files auslesen
        QXmlStreamReader::TokenType token = reader->readNext();


        // Wenn es ein "start" tag ist dann soll der Name überprüft werden
        if(token == QXmlStreamReader::StartElement)
        {

            // Ist der Name des Tags filter?
            if(reader->name() == "filter")
                // Wenn er filter ist, dann liest man aus reader den Text und teilt bei dem Steuerzeichen ; den String auf
                this->filters << reader->readElementText().split(';');


            // Ist der Name des Tags dPath?
            if(reader->name() == "dPath")
                // Wenn er dPath ist, liest man aus reader den Wert aus (String) und speichert Ihn in path
                this->path = reader->readElementText();

            // Ist der Name des Tags excluded?
            if(reader->name() == "excluded")
                // Wenn er excluded ist, dann liest man aus reader den Text und teilt bei dem Steuerzeichen ; den String auf
                this->excluded = reader->readElementText().split(";");


            // Ist der Name des Tags type?
            if(reader->name() == "type")
                // Wenn er type ist wird die speichermethode gewählt; Ist diese dem Programm nicht bekannt
                // Wird das auch ausgegeben bei der evaluierung;
                this->saveType = reader->readElementText();


            // Ist der Name des Tags excluded?
            if(reader->name() == "dest")
            {
                // Wenn er dest ist, dann liest man aus dem Reader den Text, speichert ihn in destination und
                this->destination = reader->readElementText();

                // Überprüft ob die Destination mit \ endet. Wenn nicht muss \ hinzugefügt werden.
                if(!this->destination.endsWith("\\"))
                    this->destination += "\\";

            }

        }

    }*/

    // Wurde kein SaveType gefunden wird automatisch auf local gesetzt.
    if(this->saveType.isEmpty())
        this->saveType = "local";



    // Hier wird überprüft ob path nicht leer ist UND ob der angegebene Pfad existiert
    if(path.count() && QFileInfo(path).exists())
        // Falls er das tut, ist dieser Pfad gültig
        valid = true;
}


/*
 * Default Konstruktor
 *
 * Setzt die Werte für die Instanzvariablen auf ihre Default-Werte
 */
QJsonParser::QJsonParser()
{

    // Hier werden die Default-Werte gesetzt.
    this->name        = "";
    this->valid       = false;
    this->path        = "";
    this->excluded    = QStringList();
    this->filters     = QStringList();
    this->destination = "";
    this->saveType    = "";
    this->JsonPath    = "";

}


// Gibt den Pfad des derzeitigen QXmlParser zurück. (Dieser würde von einem <dir> </dir> Tag entnommen)
QString QJsonParser::getDirPath() {
    return this->path;
}

// Gibt die excludierten Ordners des derzeitigen QXmlParser zurück. (Dieser würde von einem <dir> </dir> Tag entnommen)
QStringList QJsonParser::getExcludedDirs() {
    return this->excluded;
}


// Gibt die filter des derzeitigen QXmlParser zurück. (Dieser würde von einem <dir> </dir> Tag entnommen)
QStringList QJsonParser::getFilters() {
    return this->filters;
}


// isValid gibt an, ob der eingelesene <dir> </dir> Tag Inhalt ein gültiges Verzeichnis ist (d.h nutzbar)
bool QJsonParser::isValid() {
    return true;
   // return this->valid;
}

// Gibt den Zielort fürs Speichern zurück des derzeitigen QXmlParser Elements (Dieser wurde von <dest> </dest> Tag entnommen
QString QJsonParser::getDest() {
    return this->destination;
}

// Gibt die Art der Speicherung zurück des derzeitigen QXmlParser Elements ( Dieser wurde vom <type> </type> Tag entnommen)
QString QJsonParser::getSaveType()  {
    return this->saveType;
}

// Gibt den Pfad auf dem der Json-Auftrag gespeichert wurde; Falls dieser nicht lokal ist (am Client) wird ein leerer String zurück gegeben.
QString QJsonParser::getJsonPath() {
    return this->JsonPath;
}

// Gibt den vom user definierten Sicherungs-Aufgaben Namen zurück
QString QJsonParser::getName() {
    return this->name;
}


QString QJsonParser::getDboxKey() {
    return this->dBoxKey;
}
