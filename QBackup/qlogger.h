#ifndef QLOGGER_H
#define QLOGGER_H
#include <QtGlobal>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QtGlobal>
#include <QDir>
#include <QRegularExpression>
#include <qlogger.h>
#include <QDebug>

// Beherbergt das aktuelle QFile in welches alle Log-Einträge geschrieben werden.
static QFile       outFile(QDir::currentPath() + "\\log\\" + QDate::currentDate().toString("yyyy-MM-dd") + ".log");
// Dieses Objekt wird genutzt um Textzeilen per Line ins File zu schreiben (macht Verarbeitung einfacher)
static QTextStream ts(&outFile);

// Speichert welcher Programmteil das letzte mal den QDebug ausgeführt hat; Wird zur Ausgabe genutzt.
static QString lastFile = "";


class QLogger
{
    // Default Konstruktor & Dekonstruktor
    public:
        QLogger();
        ~QLogger();

};


static void createNewLogFile()
{


    // Falls das angelegte Log-File noch vom alten Tag ist soll dieses geupdated werden.
   if(!QString::compare(outFile.fileName(),QDate::currentDate().toString("yyyy-MM-dd") + ".log"))
   {
       // schließt das derzeitige File, damit ein neues erstellt werden kann.
       outFile.close();
       // Hier wird der Pfad des QFiles geändert;
       outFile.setFileName(QDir::currentPath() + "\\log\\" + QDate::currentDate().toString("yyyy-MM-dd") + ".log");
       // Hier öffnen wir einen Stream damit wir ins QFile über qDebug() schreiben können
       outFile.open(QIODevice::Append | QIODevice::ReadWrite | QIODevice::Text);
   }

}


static void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Deklaration und Initialisierung der Hilfsvariablen; txt speichert den Input und timeStamp ist immer die aktuelle Zeit zum Zeitpunkt des loggens.
    QString txt = "";
    QString timeStamp = "";

    if((lastFile != QString(context.file) ) )
    {
        lastFile = QString(context.file);
        timeStamp += "Called from: " + lastFile + "\n";
    }


   // Hier holen wir uns aus QT die derzeitige Zeit (Also der Zeitpunkt an dem geloggt wurde)
   timeStamp += "[ " + QTime::currentTime().toString() + " ]";


    // Dieser Switch Befehl wird genutzt um festzustellen um welche Art von Message es sich handelt. Uns ist nur die qDebug Message wichtig, den Rest ignorieren wir.
    switch (type)
    {

        // Hier wird nun der Text und der Timestamp kombiniert; timestamp + text
        case QtDebugMsg:
        {
            txt += timeStamp.append(" " + (QString("%1").arg(msg)));
            // Hier wird der erzeugte QString in den Textstream geschoben; Dieser schreibt dann automatisch in das Log-File
            ts << txt << endl;

            break;
        }

        case QtInfoMsg:
        {
            createNewLogFile();
            break;
        }


        case QtCriticalMsg:
        case QtFatalMsg:
        case QtWarningMsg:
          break;


    }


}

#endif // QLOGGER_H
