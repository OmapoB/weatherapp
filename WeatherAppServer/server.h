#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private:
    void incomingConnection(qintptr descriptor);
    void sendResponse(QTcpSocket *socket);

private slots:
    void readyRead();
};

#endif // SERVER_H
