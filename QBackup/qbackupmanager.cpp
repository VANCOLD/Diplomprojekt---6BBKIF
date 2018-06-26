#include "qbackupmanager.h"
#include <QProcess>

void QBackupManager::init()
{
    save = QJsonParser();

    if(this->readJSON(save)) {


            qDebug() << "Lesen aus File: " << save.getJsonPath();
            qDebug() << "Filter: " << save.getFilters().join(" ") << "; Exkludierte Ordner: " << save.getExcludedDirs().join(" ") << "; Zielort: " << save.getSaveType()  <<  " - " << save.getDest();
            // Input-Feld
            QString path = save.getDirPath();

            // QFileInfo Objekt, es dient zur Überprüfung welche Art von Datei der angegebene Pfad ist (File oder Ordner) und ob der Pfad existiert.
            QFileInfo check = QFileInfo(path);


            // QFileInfo kann überprüfen ob ein/e  Datei/Ordner existiert.
            // Also wenn der Pfad existiert und ein Ordner ist dann führt sich der Hauptblock aus
            if(check.exists() && check.isDir())
            {

                /*
                 * Hier gibt es 2 Fälle: Wenn der Pfad ein root ist (D.h C:\, D:\ ect) dann soll überprüft werden ob der Pfad ein \ hat
                 * Wenn nein soll es hinzugefügt werden, bei ja passiert nichts.
                 * Falls es kein Root-Ordner ist dann wird überprüft OB der Pfad mit einem \ endet.
                 * Wenn ja soll es entfernt werden, ansonsten nicht
                 */
                path = !path.endsWith(QDir::separator()) ? path + QDir::separator() : path;

                /* Das Such Objekt. Hier werden für ein QDirNode Objekt such-queries eingegeben. Pro QDirNode Root ein search.
                *  Gleichzeitig setze ich den Filter für das QDir-Object. Dieses ist eine QStringList und die QStringList Werte (Datei-Endungen) die drinnen stehen werden dann
                *  In der Daten-struktur gesucht (wird vom QDirNode gemacht;)
                */
                QDir search = QDir();
                search.setNameFilters(save.getFilters());

                // Hier erstelle ich mein QDirNode Objekt. Dazu benötige ich einen QString (Pfad) und ein QDir (ein Objekt zum Suchen)
                node = QDirNode(path,QString(),search,save.getExcludedDirs());



                int dirCount = 0, fileCount = 0;
                node.getStructureDataCount(dirCount,fileCount);

                qDebug() << "Struktur wurde angelegt!";
                qDebug() << "Ordner Anzahl: " << dirCount << "; Fileanzahl:" << fileCount << ";\n";
            }


    } else
    {
        qDebug() << "Struktur konnte nicht erstellt werden!\n";
        qDebug() << "-----------------------------------------\n\n";
        return;
    }

    qDebug() << "Backupstrukturen erfolgreich erstellt!";
    qDebug() << "-----------------------------------------\n\n";
}




bool QBackupManager::readJSON(QJsonParser &dir) {


    if(!QDir(QDir::currentPath() + "/config/").exists())
        QDir().mkdir(QDir::currentPath() + "/config/");

    QString pathBuff = QDir::currentPath() + "/config/backup-data.json";

    // File welches ausgelesen werden soll
    QFile jsonFile(pathBuff);

    // Öffnen des Files mit Lese-Rechten
    jsonFile.open(QFile::ReadOnly | QFile::Text);


    /*
    // Lese-Objekt; liest aus dem iniFile aus
    QXmlStreamReader reader(&xmlFile);



    while(!reader.atEnd() && !reader.hasError())
    {

        // Read next element
        QXmlStreamReader::TokenType token = reader.readNext();


        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument)
            continue;



        //If token is StartElement - read it
       if(token == QXmlStreamReader::StartElement)
       {

           if(reader.name() == "dir")
           {

                reader.readNext();

                QJsonParser buff = QJsonParser(&reader,pathBuff);

                if(buff.isValid())
                    dirs << buff;

           }
       }

    }*/


        QJsonParser buff = QJsonParser(jsonFile.readAll(),pathBuff);
        if(buff.isValid()) {
            dir = buff;
            jsonFile.close();
            return true;
        }



    jsonFile.close();

    return false;



}


void QBackupManager::initBackup()
{

    qDebug() << this->save.getSaveType();

    if(this->save.getSaveType() == "gdrive")
        this->gDriveSave();


    if(this->save.getSaveType() == "dbox")
        this->dBoxSave();


    if(this->save.getSaveType() == "icloud")
        this->iCloudSave();


}


void QBackupManager::gDriveSave()
{
    qDebug() << "GDRIVE-Backup isn't implemented yet";
}


void QBackupManager::dBoxSave()
{

    QStringList files;
    QString drive = node.getPath();
    node.getFilePaths(files);

    // first, we open the file
    QFile file("temp.txt");
    file.remove();
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    // now that we have a file that allows us to write anything to it,
    // we need an easy way to write out text to it
    QTextStream qout(&file);
    qout << files.join('\n');
    file.close();


    QProcess process;
    qDebug() << "Created Process";

    process.setWorkingDirectory(QDir::currentPath());

    process.setProgram("python");

    qDebug() << "test.py" <<  this->save.getDboxKey() << "" + drive << "" + QFileInfo(file).absoluteFilePath().remove(0,3) << "1";

    process.setArguments(QStringList() << "test.py" << this->save.getDboxKey()  <<  "" + drive << "" + QFileInfo(file).absoluteFilePath().remove(0,2) << "1");
    process.start(QIODevice::ReadWrite);
    process.waitForFinished();

    process.close();
    //Execute QDropbox pyhton script
    file.remove();
}


void QBackupManager::iCloudSave()
{
    qDebug() << "ICLOUD-Backup isn't implemented yet" << "\n Directory number: ";
}


