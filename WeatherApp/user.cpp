#include "user.h"

User::User()
{

}

User::User(QString name, QString login, QString password)
{
    this->name = name;
    this->login = login;
    this->password = password;
}
