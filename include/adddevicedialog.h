#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>
#include "device.h"

namespace Ui
{
    class AddDeviceDialog;
}

class AddDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDeviceDialog(QWidget *parent = nullptr);
    ~AddDeviceDialog();

    Device getDevice() const;

private:
    Ui::AddDeviceDialog *ui;
};

#endif // ADDDEVICEDIALOG_H