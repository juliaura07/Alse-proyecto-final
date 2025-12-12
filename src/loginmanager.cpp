#include "loginmanager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QCryptographicHash>
#include <QDebug>
QString Loginmanager::hashPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}
bool Loginmanager::userExists(const QString &username)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM users WHERE username = ?");
    q.addBindValue(username);
    if (q.exec() && q.next())
    {
        return q.value(0).toInt() > 0;
    }
    return false;
}

bool Loginmanager::createUser(const QString &username, const QString &password)
{
    if (username.trimmed().isEmpty() || password.isEmpty())
        return false;

    if (userExists(username))
        return false;

    QString hash = hashPassword(password);

    QSqlQuery q;
    q.prepare("INSERT INTO users (username, password_hash) VALUES (?, ?)");
    q.addBindValue(username);
    q.addBindValue(hash);
    return q.exec();
}

bool Loginmanager::login(const QString &username, const QString &password, User &userOut)
{
    QSqlQuery q;
    q.prepare("SELECT id, username, password_hash FROM users WHERE username = ?");
    q.addBindValue(QVariant(username)); // Convertir explícitamente a QVariant
    if (q.exec() && q.next())
    {
        QString dbHash = q.value("password_hash").toString();
        QString inputHash = hashPassword(password);
        if (dbHash == inputHash)
        {
            userOut.id = q.value("id").toInt();
            userOut.username = q.value("username").toString();
            userOut.passwordHash = dbHash;
            return true;
        }
    }
    return false;
}