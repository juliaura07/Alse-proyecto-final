#include <QApplication>
#include "databasemanager.h"
#include "loginwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include "loginmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!DatabaseManager::connect())
        return -1;
    DatabaseManager::initTables();

    LoginWindow login;
    if (login.exec() == QDialog::Accepted)
    {
        MainWindow w(login.getUser());
        w.show();
        return app.exec();
    }

    return 0;
}