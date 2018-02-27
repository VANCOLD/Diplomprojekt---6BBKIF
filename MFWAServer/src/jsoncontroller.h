#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#include "httprequesthandler.h"
#include "httplistener.h"

using namespace stefanfrings;

class JSonController : public HttpRequestHandler
{
    Q_OBJECT
public:
    JSonController(QObject* parent=0);
    void service(HttpRequest& request, HttpResponse& response);
    void setListener(HttpListener* myListener);

private:
    HttpListener* myListener;
};

#endif // JSONCONTROLLER_H
