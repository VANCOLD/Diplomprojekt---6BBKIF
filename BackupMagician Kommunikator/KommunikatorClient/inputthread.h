#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include <QThread>
//#include "myserver.h"

QString getustring(QString displaystring);

class InputThread : public QThread
{
    Q_OBJECT
public:
    InputThread(QObject *parent = 0);
    void run();

signals:

    gotinput(QString type, QString username, QString password);

public slots:

public slots:

private:

};

#endif // INPUTTHREAD_H
