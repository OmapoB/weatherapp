#include "loginform.h"
#include "citychooseform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QSet<User> *users, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginForm)
    , users(users)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

bool LoginForm::login(QString login, QString password)
{
    User u;
    for (auto user : *users) {
        if (user.login == login) {
            u = user;
            break;
        }
    }
    if (u.password == password) {
        return true;
    }
    return false;
}

void LoginForm::on_loginButton_clicked()
{
    if (!login(ui->loginText->text(), ui->passwordText->text())) {
        ui->infoLabel->setText("Неверный логин или пароль");
        return;
    }
    CityChooseForm* cityChooseForm = new CityChooseForm();
    cityChooseForm->show();
    close();
}

