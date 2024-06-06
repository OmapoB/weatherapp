#ifndef USER_H
#define USER_H
#include <QString>
#include <qhash.h>

class User
{
public:
    User();
    User(QString name, QString login, QString password);

    QString name;
    QString login;
    QString password;

};
inline uint qHash(const User &user, uint seed = 0) {
    return qHash(user.login, seed);
}
inline bool operator==(const User &u1, const User &u2) {
    return u1.name == u2.name &&
           u1.login == u2.login &&
           u1.password == u2.password;
}
#endif // USER_H
