#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>

namespace Ui
{
    class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RegisterWindow *ui;

    bool validateInput();
};

#endif // REGISTERWINDOW_H