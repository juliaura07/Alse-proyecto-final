#include "device.h"

Device::Device()
{
    id = -1;
    userId = -1;
    name = "";
    type = "";
    ipAddress = "";
    calibrationParams = "";
}

Device::Device(int _id, int _userId, const QString &_name, const QString &_type,
               const QString &_ip, const QString &_calib)
    : id(_id), userId(_userId), name(_name), type(_type),
      ipAddress(_ip), calibrationParams(_calib) {}