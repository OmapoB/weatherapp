#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class WeatherData : public QObject
{
    Q_OBJECT
public:
    explicit WeatherData(QString city, QObject *parent = nullptr);
    QString city;
    QDate date;
    QString weatherType;
    qint16 temperature;
    qint16 windSpeed;

    QJsonDocument toJson();

signals:
    void finished();

private slots:
    void cityRequestFinished();
    void weatherRequestFinished();

private:
    QNetworkAccessManager *manager;
    QUrl cityApiUrl;
    QUrl weatherApiUrl;
    QString latitude;
    QString longitude;
    QMap<qint16, QString> weatherCodes;

    void setApiUrls();
    void configureWeatherData();
    void initializeWeatherCodes();
};

#endif // WEATHERDATA_H
