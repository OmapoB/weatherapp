#include "server.h"
#include <QTcpSocket>
#include "response.h"
#include "weatherdata.h"
#include <QThread>

Server::Server(QObject *parent)
    : QTcpServer{parent}
{
    if (listen(QHostAddress::Any, 4000)) {
        qDebug() << "Server started!";
    } else {
        qDebug() << "Error while starting: " << errorString();
    }
}

void Server::incomingConnection(qintptr descriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(descriptor);
    qDebug() << "Connected " << descriptor;

    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
    QThread::sleep(5);
}

void Server::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    while (socket->canReadLine()) {
        QByteArray data = socket->readLine().trimmed();
        if (data.startsWith("GET")) {
            sendResponse(socket);
        }
    }
}

void Server::sendResponse(QTcpSocket *socket)
{
    QString city = socket->readAll().split('\n').last();
    WeatherData w(city);
    Response response;
    QJsonDocument msg = w.toJson();
    response.addHeader("Content-Length: " + QByteArray::number(msg.toJson().size()));
    response.setBody(msg.toJson());
    qDebug() << response.toQByteArray();

    socket->write(response.toQByteArray());
    socket->waitForBytesWritten();
    socket->disconnectFromHost();
}
