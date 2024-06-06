#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include "user.h"
#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationForm(QSet<User> *users, QWidget *parent = nullptr);
    ~RegistrationForm();

private slots:
    void on_registrationButton_clicked();

private:
    Ui::RegistrationForm *ui;
    QSet<User> *users;
    bool isRegistered(QString login);
    void registerUser();
};

#endif // REGISTRATIONFORM_H
