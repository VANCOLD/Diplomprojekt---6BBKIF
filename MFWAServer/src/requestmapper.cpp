#include "requestmapper.h"
#include "helloworldcontroller.h"
#include "listdatacontroller.h"
#include "jsoncontroller.h"

RequestMapper::RequestMapper(QObject* parent, HttpListener* myListener)
    : HttpRequestHandler(parent) {
        this->myListener = myListener;
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());

    if (path=="/" || path=="/hello") {
        HelloWorldController().service(request, response);
    }
    else if (path=="/list") {
        ListDataController().service(request, response);
    }
    else if (path== "/json")
    {
        JSonController* json = new JSonController();
        json->setListener(this->myListener);
        json->service(request,response);

    }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");
}
