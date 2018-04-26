#include <QCoreApplication>
#include "myserver.h"
#include "communicator.h"
#include <iostream>
#include <string>

QString getustring(QString displaystring)
{
    std::string stdstring;
    std::cout << displaystring.toStdString();
    std::getline (std::cin,stdstring);
    return QString::fromUtf8(stdstring.c_str());
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray response;
    Communicator mycomm;

    MyServer * mServer = NULL;

    if (mycomm.connect()) //wenn verbindung aufgebaut werden konnte
    {
        bool authenticated = mycomm.authenticate(QString("testuser1"), QString("testpassword1"), &response);

        qDebug() << QString("authenticated: ") << authenticated;
        qDebug() << QString("response from server: ").append(response);

        if (response == QByteArray("authentication successful")) //wenn authentifizierung beim server erfolgreich war -> auf message von server warten
        {
            mServer = new MyServer(); //client startet "seinen eigenen server" um zu lauschen

            QString type = getustring(QString("Please enter \"reg\" or \"auth\": "));
            QString username = getustring(QString ("Please enter username: "));
            QString password = getustring(QString("Please enter password: "));

            mycomm.senduserjson(type, username, password, &response);


            /*
            QString userstring = "";
            while (userstring != QString("quit"))
            {
                std::string stdstring;
                std::cout << "Please enter message to send to server or \"quit\" to quit: ";
                std::getline (std::cin,stdstring);
                userstring =  QString::fromUtf8(stdstring.c_str());
                //userstring = getustring(QString("Please enter message to send to server or \"quit\" to quit: "));
                mycomm.senduserstring(userstring, &response);
                qDebug() << QString("response from server: ").append(response);
            } */
        }
    }


    int ret = a.exec();
    delete mServer;
    return ret;
}


//--------
/*
class Foo
{
public:
    Foo(int x)
    {
        m_x = x;
        qDebug() << QString("constructed") << m_x;
    }

    Foo(const Foo & toCopy) : m_x(toCopy.m_x) {qDebug() << QString("copy constructed");}

    ~Foo()
    {
        qDebug() << QString("destructed") << m_x;
    }

    int get_x() const {return m_x;}
    void set_x(int x) {m_x = x;}

private:
    int m_x;
};

class Bar
{
public:
    Bar(Foo & f) : m_f(f)
    {
        f.set_x(5);
    }

private:
    Foo m_f;
};

void del(int* ptr)
{
    qDebug() << QString("before delete") << *ptr;
    delete ptr;
}

int main()
{
    int* i = new int(5);

    del(i);

    Foo* f = new Foo(1);

    qDebug() << f->get_x(); //prints 1
    {
        Bar x(*f);
    }
    qDebug() << f->get_x(); //prints 5

    delete f;

    {
        Foo y(2);
    }

    Foo g(3);

    qDebug() << f.get_x();
}
*/
