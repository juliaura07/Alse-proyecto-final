#ifndef DEVICE_H
#define DEVICE_H

#include <QString>

class Device
{
public:
    int id;
    int userId;
    QString name;
    QString type;
    QString ipAddress;
    QString calibrationParams;

    Device();
    Device(int id, int userId, const QString &name, const QString &type,
           const QString &ipAddress, const QString &calibrationParams);
};

#endif // DEVICE_H