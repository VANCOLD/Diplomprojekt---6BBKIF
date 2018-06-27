#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H

#include <QThread>
//#include "myserver.h"

class InputThread : public QThread
{
    Q_OBJECT
public:
    InputThread(QObject *parent = 0);
    void run();

signals:

    gotinput(int clientnumber, QString userstring);

public slots:

public slots:

private:

};

#endif // INPUTTHREAD_H
