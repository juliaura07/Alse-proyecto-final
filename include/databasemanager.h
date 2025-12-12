#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static bool connect();
    static void initTables();
};

#endif // DATABASEMANAGER_H