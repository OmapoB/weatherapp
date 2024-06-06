#include "registrationform.h"
#include "ui_registrationform.h"
#include "citychooseform.h"

RegistrationForm::RegistrationForm(QSet<User> *users, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegistrationForm)
    , users(users)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_registrationButton_clicked()
{
    if (isRegistered(ui->loginText->text())) {
        ui->infoLabel->setText("Пользователь уже существует");
        return;
    }
    registerUser();
    CityChooseForm* cityChooseForm = new CityChooseForm();
    cityChooseForm->show();
    close();
}

bool RegistrationForm::isRegistered(QString login)
{
    for (const User &user : *users) {
        if (user.login == login) {
            return true;
        }
    }
    return false;
}

void RegistrationForm::registerUser()
{
    User u(ui->nameText->text(), ui->loginText->text(), ui->passwordText->text());
    users->insert(u);
}
