#include "devicemanager.h"
#include <QSqlQuery>
#include <QVariant>

QList<Device> DeviceManager::getDevicesForUser(int userId)
{
    QList<Device> devices;
    QSqlQuery q;
    q.prepare("SELECT * FROM devices WHERE user_id = ?");
    q.addBindValue(userId);
    q.exec();
    while (q.next())
    {
        Device d;
        d.id = q.value("id").toInt();
        d.userId = q.value("user_id").toInt();
        d.name = q.value("name").toString();
        d.type = q.value("type").toString();
        d.ipAddress = q.value("ip_address").toString();
        d.calibrationParams = q.value("calibration_params").toString();
        devices.append(d);
    }
    return devices;
}

bool DeviceManager::addDevice(const Device &d)
{
    QSqlQuery q;
    q.prepare("INSERT INTO devices (user_id, name, type, ip_address, calibration_params) "
              "VALUES (?, ?, ?, ?, ?)");
    q.addBindValue(d.userId);
    q.addBindValue(d.name);
    q.addBindValue(d.type);
    q.addBindValue(d.ipAddress);
    q.addBindValue(d.calibrationParams);
    return q.exec();
}

bool DeviceManager::updateDevice(const Device &d)
{
    QSqlQuery q;
    q.prepare("UPDATE devices SET name = ?, type = ?, ip_address = ?, calibration_params = ? "
              "WHERE id = ?");
    q.addBindValue(d.name);
    q.addBindValue(d.type);
    q.addBindValue(d.ipAddress);
    q.addBindValue(d.calibrationParams);
    q.addBindValue(d.id);
    return q.exec();
}

bool DeviceManager::deleteDevice(int id)
{
    QSqlQuery q;
    q.prepare("DELETE FROM devices WHERE id = ?");
    q.addBindValue(id);
    return q.exec();
}