#include "jsoncontroller.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

JSonController::JSonController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

JSonController::~JSonController()
{
    delete this->myListener;
}

void JSonController::setListener(HttpListener* myListener) {
    this->myListener = myListener;
}

void JSonController::service(HttpRequest &request, HttpResponse &response) {
    QJsonDocument jsondoc = QJsonDocument::fromJson(request.getBody());
    QJsonObject jsonobj = jsondoc.object();

    if (jsonobj.contains(QString("type")))
    {
        if (jsonobj.value(QString("type")) == QJsonValue("authentication"))
        {
            if (jsonobj.value(QString("username")) == QJsonValue("testuser1"))
            {
                if (jsonobj.value(QString("password")) == QJsonValue("testpassword1"))
                {    response.write("authentication successful", true);

                   emit myListener->signaltowaitandsend();
                    qDebug("signal emitted");
                }
                else response.write("wrong password", true);
            }
            else response.write("unknown user", true);
        }
        else response.write("Warning: Received JSon of unknown type", true);
    }
    else response.write("Warning: Received JSon without \"type\" key", true);

/*  QStringList jsonkeys = jsonobj.keys();
    QString responsestring = QString("");
    for (int i = 0; i < jsonkeys.size(); ++i) {
               responsestring.append(jsonkeys.at(i).toLocal8Bit().constData());
               responsestring.append(" ");
    }

    response.write("Received the following keys: ");
    response.write(responsestring.toLatin1(),true); */
}

