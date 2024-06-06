#ifndef LOGINFORM_H
#define LOGINFORM_H

#include "user.h"
#include <QMainWindow>
#include <QMap>

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QSet<User> *users, QWidget *parent = nullptr);
    ~LoginForm();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginForm *ui;
    QSet<User> *users;

    bool login(QString login, QString password);
};

#endif // LOGINFORM_H
