#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "device.h"
#include <QList>

class DeviceManager
{
public:
    static QList<Device> getDevicesForUser(int userId);
    static bool addDevice(const Device &device);
    static bool updateDevice(const Device &device);
    static bool deleteDevice(int deviceId);
};

#endif // DEVICEMANAGER_H