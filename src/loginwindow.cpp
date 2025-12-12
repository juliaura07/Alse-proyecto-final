#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "loginmanager.h"
#include "registerwindow.h"
#include <QMessageBox>
LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent),
                                            ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false); // Ocultar mensaje de error al inicio
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

User LoginWindow::getUser() const
{
    return loggedUser;
}
void LoginWindow::on_registerButton_clicked()
{
    RegisterWindow registerDialog(this);
    if (registerDialog.exec() == QDialog::Accepted)
    {
        QMessageBox::information(this, "Registro exitoso", "Usuario creado con éxito. Ahora puedes iniciar sesión.");
    }
}
void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    User user;
    if (Loginmanager::login(username, password, user))
    {
        loggedUser = user;
        accept(); // Cierra el diálogo con estado "aceptado"
    }
    else
    {
        ui->errorLabel->setText("Usuario o contraseña incorrectos");
        ui->errorLabel->setVisible(true);
    }
}