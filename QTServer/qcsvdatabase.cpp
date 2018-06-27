#include "qcsvdatabase.h"
#include <QDebug>

QCsvDatabase::QCsvDatabase()
{

    data = QStringList();
    QFile users(QDir::currentPath() + "\\db\\users.csv");
    users.open(QIODevice::ReadOnly|QIODevice::Text);

    QTextStream usersT(&users);

    do
    {

        QString line         = usersT.readLine();
        qDebug() << line;
        data << line;
    } while(!usersT.atEnd());

}


bool QCsvDatabase::checkUser(QString user)
{

    foreach(QString entry, data)
    {
        if( entry.contains(user + ";"))
            return true;
    }
    return false;
}

bool QCsvDatabase::userLogin(QString user, QString pass)
{

    foreach(QString entry, data)
    {
        qDebug() << entry;
        if(entry.contains(user + ";" + pass))
            return true;



    }

    return false;
}


int QCsvDatabase::getUserID(QString user, QString pass) {


    foreach(QString entry, data)
    {
        if(entry.contains(user + ";" + pass))
            return QString(entry.at(0)).toInt();


    }
    return -1;
}

int QCsvDatabase::getUserCount()
{
    return data.length();
}

void QCsvDatabase::addUser(QString user, QString pass)
{

    QFile users(QDir::currentPath() + "\\db\\users.csv");
    users.open(QIODevice::ReadWrite|QIODevice::Text);

    QTextStream usersT(&users);
    usersT.readAll();
    usersT << "\n" << QString::number(getUserCount()) + ";" + user + ";" + pass;
    qDebug()<< "test" << QString::number(getUserCount()) + ";" + user + ";" + pass;
    users.close();

    data << QString::number(getUserCount()) + ";" + user + ";" + pass;
}

void QCsvDatabase::addDirs(int uID, QString dirs)
{

    QFile dirFile(QDir::currentPath() + "\\db\\dirs.csv");
    dirFile.open(QIODevice::ReadWrite|QIODevice::Text);

    QTextStream dirT(&dirFile);
    QStringList buff = dirs.replace('\n',';').split(';');


    foreach(QString entry, buff)
        dirT << QString::number(uID) + ";" + entry + "\n";


    dirFile.close();
}

void QCsvDatabase::addCloudData(int uID,QString key) {

}
