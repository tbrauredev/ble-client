//==============================================================================
// Copyright (C) 2023 Thomas Braure.
//
// This file is part of ble-client.
//
// ble-client is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ble-client is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ble-client. If not, see <https://www.gnu.org/licenses/>.
//==============================================================================

#ifndef DEVICES_MODEL_H_
#define DEVICES_MODEL_H_

#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/QBluetoothUuid>
#include <QtCore/QAbstractListModel>

class DevicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum class Roles {
        Name = Qt::UserRole + 1,
        Address = Qt::UserRole + 2,
        Uuid = Qt::UserRole + 3,
    };
    Q_ENUM(Roles);

    explicit DevicesModel(QObject* parent = nullptr);

    DevicesModel(const DevicesModel&) = delete;
    DevicesModel(DevicesModel&&) = delete;

    DevicesModel& operator = (const DevicesModel&) = delete;
    DevicesModel& operator = (DevicesModel&&) = delete;

    ~DevicesModel() override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant device(int row) const;

    QList<QBluetoothDeviceInfo> deviceInfos() const;
    QBluetoothDeviceInfo deviceInfo(int row) const;

    void addDeviceInfo(const QBluetoothDeviceInfo& info);
    void removeDeviceInfo(const QBluetoothDeviceInfo& info);

    void clearDeviceInfos();

private:
    QList<QBluetoothDeviceInfo> m_deviceInfos;
};

#endif  // DEVICES_MODEL_H_
