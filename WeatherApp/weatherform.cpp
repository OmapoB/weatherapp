#include "weatherform.h"
#include "citychooseform.h"
#include "ui_weatherform.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QUrl>

WeatherForm::WeatherForm(QString city, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::WeatherForm),
    manager(new QNetworkAccessManager(this))
{
    getWeather(city);
    ui->setupUi(this);
}

WeatherForm::~WeatherForm()
{
    delete ui;
}

void WeatherForm::on_pushButton_clicked()
{
    CityChooseForm* cityForm = new CityChooseForm();
    cityForm->show();
    close();
}

void WeatherForm::onWeatherGot()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
    qDebug() << response["temperature"];
    ui->cityLabel->setText(response["city"].toString());
    ui->weatherTypeLabel->setText(response["weather_type"].toString());
    ui->temperatureLabel->setText(QString::number(response["temperature"].toDouble()).append(" °C"));
    ui->windSpeedLabel->setText(QString::number(response["wind_speed"].toDouble()).append(" м/с"));
    QDate date = QDate::fromString(response["date"].toString());
    ui->dayMonthLabel->setText(QString("%1, %2")
                                   .arg(date.day(), 1)
                                   .arg(QLocale(QLocale::Russian).monthName(date.month()), 2)
                               );
    ui->yearLabel->setText(QString::number(date.year()));
    ui->weekDayLabel->setText(QLocale(QLocale::Russian).dayName(date.dayOfWeek()));
}

void WeatherForm::getWeather(QString city)
{
    QNetworkRequest request(QUrl("http://localhost:4000"));
    QByteArray msg;
    msg.append(city.toStdString());
    QNetworkReply* reply = manager->get(request, msg);
    connect(reply, &QNetworkReply::finished, this, &WeatherForm::onWeatherGot);

}

