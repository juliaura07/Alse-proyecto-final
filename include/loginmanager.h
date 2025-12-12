#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "user.h"
#include <QString>

class Loginmanager
{
public:
    static bool login(const QString &username, const QString &password, User &userOut);
    static QString hashPassword(const QString &password);
    static bool userExists(const QString &username);
    static bool createUser(const QString &username, const QString &password);
};

#endif // LOGINMANAGER_H