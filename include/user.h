#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    int id;
    QString username;
    QString passwordHash;

    User();
    User(int id, const QString &username, const QString &passwordHash);
};

#endif // USER_H