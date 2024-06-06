#ifndef WEATHERFORM_H
#define WEATHERFORM_H

#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class WeatherForm;
}

class WeatherForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit WeatherForm(QString city, QWidget *parent = nullptr);
    ~WeatherForm();

private slots:
    void on_pushButton_clicked();
    void onWeatherGot();

private:
    Ui::WeatherForm *ui;
    QNetworkAccessManager* manager;

    void getWeather(QString city);
};

#endif // WEATHERFORM_H
