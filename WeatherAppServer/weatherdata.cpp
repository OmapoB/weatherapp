#include "weatherdata.h"
#include <QEventLoop>

WeatherData::WeatherData(QString city, QObject *parent)
    : QObject{parent}, city{city}
{
    manager = new QNetworkAccessManager(this);
    QEventLoop loop;
    configureWeatherData();
    connect(this, &WeatherData::finished, &loop, &QEventLoop::quit);
    loop.exec();
}

QJsonDocument WeatherData::toJson()
{
    QJsonObject json = {
        {"city", city},
        {"date", date.toString()},
        {"temperature", temperature},
        {"wind_speed", windSpeed},
        {"weather_type", weatherType}
    };
    return QJsonDocument(json);
}

void WeatherData::cityRequestFinished(){
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
    QJsonObject coordinates = response["results"]
                                  .toArray()[0]
                                  .toObject();
    latitude = QString::number(coordinates["latitude"].toDouble());
    longitude = QString::number(coordinates["longitude"].toDouble());

    weatherApiUrl.setUrl("https://api.open-meteo.com/v1/forecast");
    QUrlQuery query(weatherApiUrl.query());
    query.addQueryItem("latitude", latitude);
    query.addQueryItem("longitude", longitude);
    query.addQueryItem("current", "temperature_2m,weather_code,wind_speed_10m");
    weatherApiUrl.setQuery(query);
    qDebug() << weatherApiUrl;

    QNetworkRequest weatherRequest(weatherApiUrl);
    QNetworkReply *weatherReply = manager->get(weatherRequest);
    connect(weatherReply, &QNetworkReply::finished,
            this, &WeatherData::weatherRequestFinished);
}

void WeatherData::weatherRequestFinished(){
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
    QJsonObject data = response["current"].toObject();
    temperature = data["temperature_2m"].toDouble();
    date = QDate::fromString(data["time"].toString(), Qt::DateFormat::ISODate);
    windSpeed = data["wind_speed_10m"].toDouble();
    weatherType = data["weather_code"].toString();
    emit finished();
}

void WeatherData::setApiUrls(){
    cityApiUrl.setUrl("https://public.opendatasoft.com/api/explore/v2.1/catalog/datasets/geonames-postal-code/records");
    QUrlQuery query(cityApiUrl.query());
    query.addQueryItem("select", "latitude,longitude");
    QString where = QString("place_name=\"%1\"").arg(city);
    query.addQueryItem("where", where);
    query.addQueryItem("limit", "1");
    cityApiUrl.setQuery(query);
    qDebug() << cityApiUrl;
}

void WeatherData::configureWeatherData(){
    setApiUrls();
    QNetworkRequest cityRequest(cityApiUrl);
    QNetworkReply *cityReply = manager->get(cityRequest);
    connect(cityReply, &QNetworkReply::finished,
            this, &WeatherData::cityRequestFinished);
}

void WeatherData::initializeWeatherCodes()
{
    weatherCodes[0] = "Ясно";
    weatherCodes[1] = "Ясно";
    weatherCodes[2] = "Переменная\nоблачность";
    weatherCodes[3] = "Пасмурно";
    weatherCodes[45] = "Туман";
    weatherCodes[48] = "Туман";
    weatherCodes[51] = "Легкая\nморось";
    weatherCodes[53] = "Морось";
    weatherCodes[55] = "Сильная\nморос";
    weatherCodes[56] = "Легкая\nизморозь";
    weatherCodes[57] = "Изморозь";
    weatherCodes[61] = "Легкий\nдождь";
    weatherCodes[63] = "Дождь";
    weatherCodes[65] = "Сильный\nдождь";
    weatherCodes[66] = "Ледяной\nдождь";
    weatherCodes[67] = "Ледяной\nдождь";
    weatherCodes[71] = "Легкий\nснегопад";
    weatherCodes[72] = "Снегопад";
    weatherCodes[73] = "Сильный\nснегопад";
    weatherCodes[77] = "Крупный\nснег";
    weatherCodes[80] = "Легкий\nливень";
    weatherCodes[81] = "Ливень";
    weatherCodes[82] = "Сильный\nливень";
    weatherCodes[85] = "Легкая\nметель";
    weatherCodes[86] = "Сильная\nметель";
    weatherCodes[95] = "Гроза";
    weatherCodes[96] = "Гроза\nс градом";
    weatherCodes[99] = "Гроза\nс градом";
}
