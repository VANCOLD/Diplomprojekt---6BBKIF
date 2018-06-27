#ifndef QLOGGER_H
#define QLOGGER_H
#include <QtGlobal>
#include <QDebug>
#include "ui_mainwindow.h"


class QLogger
{
    // Default Konstruktor & Dekonstruktor
    public:
        QLogger();
        ~QLogger();
        void setLogger(Ui::MainWindow* ui);
        static Ui::MainWindow* myUI;


        static void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
        {

            // Dieser Switch Befehl wird genutzt um festzustellen um welche Art von Message es sich handelt. Uns ist nur die qDebug Message wichtig, den Rest ignorieren wir.
            switch (type)
            {

                // Hier wird nun der Text und der Timestamp kombiniert; timestamp + text
                case QtDebugMsg:
                {
                    myUI->status->setText(msg);
                    qDebug() << "test123123";
                    break;
                }

                case QtInfoMsg:
                case QtCriticalMsg:
                case QtFatalMsg:
                case QtWarningMsg:
                  break;


            }


        }

};



#endif // QLOGGER_H
