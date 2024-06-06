#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginform.h"
#include "registrationform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    users = new QSet<User>;
    initializeUsers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    qDebug() << users->size();
    LoginForm* loginForm = new LoginForm(users);
    loginForm->show();
    close();
}


void MainWindow::on_registrationButton_clicked()
{
    RegistrationForm* registrationForm = new RegistrationForm(users);
    registrationForm->show();
    close();
}

void MainWindow::initializeUsers()
{
    User *u = new User("Мага", "admin", "123456");
    users->insert(*u);
}

