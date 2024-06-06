#include "response.h"
#include "qdebug.h"

Response::Response() {
    initializeDefaultHeaders();
}

QByteArray Response::toQByteArray() {
    QByteArray result;
    for (auto value : headers) {
        result.append(value.toStdString())
            .append(delimeter.toStdString());
    }
    result.append(delimeter.toStdString())
        .append(body.toStdString());
    return result;
}

void Response::addHeader(QString value)
{
    headers.append(value);
}

void Response::setBody(QString body)
{
    this->body = body;
}

void Response::initializeDefaultHeaders()
{
    headers.append("HTTP/1.1 200 OK");
    headers.append("Content-Type: application/json");
}
