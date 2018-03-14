#include "jsoncontroller.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

JSonController::JSonController(QObject* parent)
    : HttpRequestHandler(parent) {
    // empty
}

void JSonController::service(HttpRequest &request, HttpResponse &response) {
    QJsonDocument jsondoc = QJsonDocument::fromJson(request.getBody());
    QJsonObject jsonobj = jsondoc.object();

    if (jsonobj.contains(QString("type")))
    {
        if (jsonobj.value(QString("type")) == QJsonValue("authentication"))
        {
             response.write("you're the server, server! you don't need to authenticate to me!", true);
        }
        else if (jsonobj.value(QString("type"))== QJsonValue("debug"))
        {
            response.write("received your debug-json", true);
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

