#include <QCoreApplication>
#include "myserver.h"
#include "communicator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray auth_response;
    Communicator mycomm;

    bool authenticated = mycomm.authenticate(QString("testuser1"), QString("testpassword1"), &auth_response);

    qDebug() << QString("authenticated: ") << authenticated;
    qDebug() << QString("auth_response: ").append(auth_response);

    MyServer * mServer = NULL;
    if (auth_response == QByteArray("authentication successful")) //wenn authentifizierung beim server erfolgreich war -> auf message von server warten
    {
        mServer = new MyServer(); //client startet "seinen eigenen server" um zu lauschen
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
