#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddevicedialog.h"
#include "devicemanager.h"
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QLineEdit>
#include "loginwindow.h"
#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(const User &user, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentUser(user)
{
    ui->setupUi(this);

    ui->deviceTableWidget->setColumnCount(5);
    ui->deviceTableWidget->setHorizontalHeaderLabels(QStringList()
                                                     << "Nombre" << "Tipo" << "IP" << "Calibración" << "Estado");
    ui->deviceTableWidget->horizontalHeader()->setStretchLastSection(true);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::onActionLogoutTriggered);

    loadDevices();
    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &MainWindow::updateDeviceStatuses);
    statusTimer->start(10000); // cada 10 segundos

    connect(ui->refreshIntervalSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](int seconds)
            {
                statusTimer->setInterval(seconds * 1000); // convertir a milisegundos
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDevices()
{
    QList<Device> devices = DeviceManager::getDevicesForUser(currentUser.id);
    ui->deviceTableWidget->setRowCount(devices.size());
    ui->deviceTableWidget->setColumnCount(5);
    ui->deviceTableWidget->setHorizontalHeaderLabels(QStringList()
                                                     << "Nombre" << "Tipo" << "IP" << "Calibración" << "Estado");

    for (int i = 0; i < devices.size(); ++i)
    {
        const Device &d = devices[i];
        ui->deviceTableWidget->setItem(i, 0, new QTableWidgetItem(d.name));
        ui->deviceTableWidget->setItem(i, 1, new QTableWidgetItem(d.type));
        ui->deviceTableWidget->setItem(i, 2, new QTableWidgetItem(d.ipAddress));
        ui->deviceTableWidget->setItem(i, 3, new QTableWidgetItem(d.calibrationParams));

        QTableWidgetItem *estadoItem = new QTableWidgetItem("Verificando...");
        estadoItem->setForeground(Qt::gray);
        ui->deviceTableWidget->setItem(i, 4, estadoItem);
    }
}

void MainWindow::onAddButtonClicked()
{
    AddDeviceDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Device newDevice = dialog.getDevice();
        newDevice.userId = currentUser.id;

        if (DeviceManager::addDevice(newDevice))
        {
            loadDevices();
        }
        else
        {
            QMessageBox::warning(this, "Error", "No se pudo agregar el dispositivo.");
        }
    }
}

void MainWindow::onActionLogoutTriggered()
{
    this->close();

    LoginWindow loginDialog;
    if (loginDialog.exec() == QDialog::Accepted)
    {
        MainWindow *newMain = new MainWindow(loginDialog.getUser());
        newMain->show();
    }
    else
    {
        qApp->quit();
    }
}

void MainWindow::onEditButtonClicked()
{
    int selectedRow = ui->deviceTableWidget->currentRow();
    if (selectedRow < 0)
    {
        QMessageBox::information(this, "Editar", "Selecciona un dispositivo para editar.");
        return;
    }

    QList<Device> devices = DeviceManager::getDevicesForUser(currentUser.id);
    if (selectedRow >= devices.size())
        return;

    Device d = devices[selectedRow];

    AddDeviceDialog dialog(this);

    dialog.findChild<QLineEdit *>("lineEditName")->setText(d.name);
    dialog.findChild<QLineEdit *>("lineEditType")->setText(d.type);
    dialog.findChild<QLineEdit *>("lineEditIP")->setText(d.ipAddress);
    dialog.findChild<QLineEdit *>("lineEditCalibration")->setText(d.calibrationParams);

    if (dialog.exec() == QDialog::Accepted)
    {
        Device updated = dialog.getDevice();
        updated.id = d.id;
        updated.userId = d.userId;

        if (DeviceManager::updateDevice(updated))
        {
            loadDevices();
        }
        else
        {
            QMessageBox::warning(this, "Error", "No se pudo actualizar el dispositivo.");
        }
    }
}

void MainWindow::onDeleteButtonClicked()
{
    int selectedRow = ui->deviceTableWidget->currentRow();
    if (selectedRow < 0)
    {
        QMessageBox::information(this, "Eliminar", "Selecciona un dispositivo para eliminar.");
        return;
    }

    QList<Device> devices = DeviceManager::getDevicesForUser(currentUser.id);
    if (selectedRow >= devices.size())
        return;

    Device d = devices[selectedRow];

    auto reply = QMessageBox::question(this, "Eliminar",
                                       QString("¿Seguro que quieres eliminar el dispositivo '%1'?").arg(d.name),
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        if (DeviceManager::deleteDevice(d.id))
        {
            loadDevices();
        }
        else
        {
            QMessageBox::warning(this, "Error", "No se pudo eliminar el dispositivo.");
        }
    }
}

void MainWindow::updateDeviceStatuses()
{
    for (int i = 0; i < ui->deviceTableWidget->rowCount(); ++i)
    {
        QString ip = ui->deviceTableWidget->item(i, 2)->text();

        // Simulación: 50% de probabilidad de estar activo
        bool activo = (QRandomGenerator::global()->bounded(2) == 1);

        QString estadoTexto = activo ? "Activo" : "Inactivo";
        QTableWidgetItem *estadoItem = new QTableWidgetItem(estadoTexto);
        estadoItem->setForeground(activo ? Qt::green : Qt::red);

        ui->deviceTableWidget->setItem(i, 4, estadoItem);
    }
}