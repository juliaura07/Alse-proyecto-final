#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer> //usar Qtimer
#include "user.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const User &user, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadDevices();
    void onAddButtonClicked();
    void onEditButtonClicked();
    void onDeleteButtonClicked();
    void onActionLogoutTriggered();
    void updateDeviceStatuses();

private:
    Ui::MainWindow *ui;
    User currentUser;
    QTimer *statusTimer; // temporizador para actualizar el estado
};

#endif // MAINWINDOW_H