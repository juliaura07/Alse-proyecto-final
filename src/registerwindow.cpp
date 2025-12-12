#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "loginmanager.h"
#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &RegisterWindow::reject);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

bool RegisterWindow::validateInput()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString pass1 = ui->lineEditPassword->text();
    QString pass2 = ui->lineEditConfirm->text();

    if (username.isEmpty() || pass1.isEmpty() || pass2.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return false;
    }

    if (pass1 != pass2)
    {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return false;
    }

    return true;
}

void RegisterWindow::on_buttonBox_accepted()
{
    if (!validateInput())
        return;

    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text();

    if (Loginmanager::userExists(username))
    {
        QMessageBox::warning(this, "Error", "El usuario ya existe.");
        return;
    }

    if (Loginmanager::createUser(username, password))
    {
        accept(); // Solo si el usuario se creó correctamente
    }
    else
    {
        QMessageBox::warning(this, "Error", "No se pudo crear el usuario.");
    }
}