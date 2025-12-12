#include "user.h"

User::User()
{
    id = -1;
    username = "";
    passwordHash = "";
}

User::User(int _id, const QString &_username, const QString &_passwordHash)
    : id(_id), username(_username), passwordHash(_passwordHash) {}