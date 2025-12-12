#include "adddevicedialog.h"
#include "ui_adddevicedialog.h"

AddDeviceDialog::AddDeviceDialog(QWidget *parent) : QDialog(parent),
                                                    ui(new Ui::AddDeviceDialog)
{
    ui->setupUi(this);

    // Conectar botones OK/Cancel automáticamente
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddDeviceDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &AddDeviceDialog::reject);
}

AddDeviceDialog::~AddDeviceDialog()
{
    delete ui;
}

Device AddDeviceDialog::getDevice() const
{
    Device d;
    d.name = ui->lineEditName->text();
    d.type = ui->lineEditType->text();
    d.ipAddress = ui->lineEditIP->text();
    d.calibrationParams = ui->lineEditCalibration->text();
    return d;
}