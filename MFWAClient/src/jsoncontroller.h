#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

class JSonController : public HttpRequestHandler
{
    Q_OBJECT
public:
    JSonController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
};

#endif // JSONCONTROLLER_H
