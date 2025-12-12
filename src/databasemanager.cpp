#include "databasemanager.h"
#include <QSqlQuery>
#include <QDebug>
#include "loginmanager.h"
bool DatabaseManager::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("iot_config.db");
    return db.open();
}

void DatabaseManager::initTables()
{
    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS users ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "username TEXT UNIQUE,"
           "password_hash TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS devices ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "user_id INTEGER,"
           "name TEXT,"
           "type TEXT,"
           "ip_address TEXT,"
           "calibration_params TEXT,"
           "FOREIGN KEY(user_id) REFERENCES users(id))");
}