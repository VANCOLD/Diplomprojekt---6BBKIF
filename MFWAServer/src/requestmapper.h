#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "httplistener.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
public:
    RequestMapper(QObject* parent=0,HttpListener* myListener = 0);
    void service(HttpRequest& request, HttpResponse& response);

private:
    HttpListener* myListener;


};

#endif // REQUESTMAPPER_H
