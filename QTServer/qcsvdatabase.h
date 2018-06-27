#ifndef QCSVDATABASE_H
#define QCSVDATABASE_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>

class QCsvDatabase
{
public:

    QCsvDatabase();

    bool checkUser(QString user);
    bool userLogin(QString user, QString pass);
    int  getUserID(QString user, QString pass);
    void addUser(QString user, QString pass);
    void addDirs(int uID, QString dirs);
    void addCloudData(int uID, QString key);
    int getUserCount();

private:
    QStringList data;
};

#endif // QCSVDATABASE_H
