#ifndef RESPONSE_H
#define RESPONSE_H

#include <Qstring>
#include <QList>
#include <QByteArray>

class Response
{
public:
    Response();
    QByteArray toQByteArray();
    void addHeader(QString value);
    void setBody(QString body);

private:
    const QString delimeter = "\r\n";
    QList<QString> headers;
    QString body;

    void initializeDefaultHeaders();
};

#endif // RESPONSE_H
