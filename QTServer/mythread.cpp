#include "mythread.h"


MyThread::MyThread(int ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    //thread starts here
    qDebug() << socketDescriptor << "Starting thread";
    socket = new QTcpSocket();
    db = QCsvDatabase();

    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    qDebug() << "before connecting gotinput to writesocket";
    connect(this->ithread, SIGNAL(gotinput(int /*clientnumber*/, QString /*userstring*/)), this, SLOT(writetosocket(int /*clientnumber*/, QString /*userstring*/)));
    qDebug() << "after connecting gotinput to writesocket";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socketDescriptor << "Client connected";

    exec();
}

void MyThread::setinputthread(InputThread *ithread)
{
    this->ithread = ithread;
}

void MyThread::writetosocket(int clientnumber, QString userstring)
{
    if(this->socketDescriptor == clientnumber)
    {
        QByteArray tempContent(userstring.toUtf8());
        socket->write(tempContent);
        socket->waitForBytesWritten(1000);
    }
}


void MyThread::readyRead()
{
    QByteArray Data = socket->readAll();
    qDebug() << socketDescriptor << "Data in: " << Data;

    QJsonDocument jsondoc = QJsonDocument::fromJson(Data);
    QJsonObject jsonobj = jsondoc.object();
    QString type = jsonobj["type"].toString();

    if (!type.isEmpty())
    {

        QString user = jsonobj["username"].toString();
        QString pass = jsonobj["password"].toString();


        if(type == "task") {

        }

        if(type == "dirs")
        {
            if(db.userLogin(user,pass))
            {
                QString dirs = jsonobj["dirs"].toString();
                int uID = db.getUserID(user,pass);
                db.addDirs(uID,dirs);

                socket->write("dirs added successfully");
                emit signaltowaitandsend(jsonobj.value(QString("clientport")).toInt());

            } else {
                socket->write("dirs errror");
                emit signaltowaitandsend(jsonobj.value(QString("clientport")).toInt());

            }
        }

        if(type == "clouddata")
        {
            if(db.userLogin(user,pass))
            {
                QString dirs = jsonobj["cloudData"].toString();
                int uID = db.getUserID(user,pass);
                db.addCloudData(uID,dirs);

                socket->write("clouddata added successfully");
                emit signaltowaitandsend(jsonobj.value(QString("clientport")).toInt());

            } else {
                socket->write("clouddata error");
                emit signaltowaitandsend(jsonobj.value(QString("clientport")).toInt());
            }
        }

        if (type == "authentication")
        {

            if(db.userLogin(user,pass))
            {

                   qDebug() << QHostAddress(socket->peerAddress().toIPv4Address()).toString();
                   socket->write("auth successful");
                   emit signaltowaitandsend(jsonobj.value(QString("clientport")).toInt());
                   qDebug("signaltowaitandsend emitted");

            } else socket->write("User not found");
        }

        if (type == "register")
        {
            if(!db.checkUser(user)) {

                socket->write("registry successful");

                db.addUser(user,pass);
                qDebug() << QHostAddress(socket->peerAddress().toIPv4Address()).toString();

            } else {
                socket->write("registry unsuccesful");
            }
        }

    }

    else socket->write("Warning: Received JSon without \"type\" key");
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    socket->deleteLater();
    exit(0);
}
