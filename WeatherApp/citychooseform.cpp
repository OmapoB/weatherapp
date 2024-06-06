#include "citychooseform.h"
#include "ui_citychooseform.h"
#include "weatherform.h"

CityChooseForm::CityChooseForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CityChooseForm)
{
    ui->setupUi(this);
}

CityChooseForm::~CityChooseForm()
{
    delete ui;
}

void CityChooseForm::on_cityEnterButton_clicked()
{
    WeatherForm* weatherForm = new WeatherForm(ui->cityText->text());
    weatherForm->show();
    close();
}
