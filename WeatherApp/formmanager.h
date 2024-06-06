#ifndef FROMMANAGER_H
#define FROMMANAGER_H

#include "loginform.h"
#include "mainwindow.h"
#include "registrationform.h"

#include <QObject>

class FormManager : public QObject
{
    Q_OBJECT
public:
    FormManager();

private:
    MainWindow* mainForm;
    RegistrationForm* registartionForm;
    LoginForm* loginForm;
    CityChooseForm* cityForm;
    WeatherForm* weatherForm;

    void startApp();
};

#endif // FROMMANAGER_H
