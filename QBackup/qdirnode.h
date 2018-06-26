#ifndef QDIRNODE_H
#define QDIRNODE_H
#include <QString>
#include <QDir>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QDateTime>

using namespace std;

class QDirNode
{

public:


    // ** Konstruktoren ** //
        QDirNode(QString path, QString dirPath ,QDir search,QStringList excluded);
        QDirNode();

        ~QDirNode();


     // ** Setter & Getter Funktionen ** //

        // Pfad Funktionen
        void getStructureDataCount(int &dirCount,int &fileCount);


    // ** QDirNode Abfrage & Bearbeitungs-Funktionen ** //

        // Die Funktion getDataPaths iteriert rekursiv durch alle QDirNodes und speichert die Inhalte und gibt diese zurück.
        void getDataPaths(QStringList &pathList);

        // Siehe Beschreibung getDataPaths; INFO: Unterschied ist das NUR File-Paths zurückgegeben werden
        void getFileNames(QStringList &nameList);

        // Siehe Beschreibung getDataPaths; INFO: Unterschied ist das NUR Directory-Paths zurückgegeben werden
        void getDirPaths(QStringList &pathList);

        // Siehe Beschreibung getDataPaths; INFO: Unterschied ist das NUR File-Paths zurückgegeben werden
        void getFilePaths(QStringList &pathList);

        // Speichert alle Files und Ordner in referenzierte QStringList Objekte (Werden intern genutzt und dann in data gespeichert).
        void fetchData(QDir search, QStringList &dirs);

        void createSubnodes(QStringList dirs, QDir search, QStringList excluded);

        void updateStructure(QDateTime timestamp);

        QString getPath();

        int getdCount();
        int getfCount();


private:


    QMap<QString,QDirNode> nodes;

    // Speichert alle Files die zu speichern sind
    QStringList data;

    // speichert alle Ordner die zu speichern sind
    QStringList dirs;

    // Unterordneranzahl im QDirNode-Objekt (Ordner)
    int dCount;

    // Fileanzahl im QDirNode-Objekt)
    int fCount;

    // Pfad-Teil welches jeder Ordner im QDirNode-Konstrukt besitzt.
    QString path;

    // Spezifische Verzweigung (Ordner Pfad) INNERHALB des QDirNode Konstrukts (wird benötigt zum Speichern)
    QString dirPath;

    QStringList searchFilter;

    QStringList excluded;



};





#endif // QDIRNODE_H
