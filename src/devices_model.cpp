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
//
#include "devices_model.h"

DevicesModel::DevicesModel(QObject* parent) :
    QAbstractListModel(parent) {}

DevicesModel::~DevicesModel() {}

int DevicesModel::rowCount(const QModelIndex& parent) const
{
    return m_deviceInfos.count();
}

QVariant DevicesModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= m_deviceInfos.count())
        return QVariant();

    QBluetoothDeviceInfo info = m_deviceInfos[index.row()];
    switch (static_cast<Roles>(role)) {
        case Roles::Name:
            return info.name();

        case Roles::Address:
            return info.address().toString();

        case Roles::Uuid:
            return info.deviceUuid().toString(QUuid::WithoutBraces);

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> DevicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::Name)] = "name";
    roles[static_cast<int>(Roles::Address)] = "address";
    roles[static_cast<int>(Roles::Uuid)] = "uuid";
    return roles;
}

QVariant DevicesModel::device(int row) const
{
    if (row >= m_deviceInfos.count())
        return QVariant();

    QVariantMap deviceMap;
    QModelIndex index = this->index(row, 0);

    QHash<int, QByteArray> roleNames = this->roleNames();
    for (int role : roleNames.keys())
        deviceMap.insert(roleNames[role], this->data(index, role));

    return deviceMap;
}

QList<QBluetoothDeviceInfo> DevicesModel::deviceInfos() const
{
    return m_deviceInfos;
}

QBluetoothDeviceInfo DevicesModel::deviceInfo(int row) const
{
    if (row < m_deviceInfos.count())
        return m_deviceInfos[row];
    else
        return QBluetoothDeviceInfo();
}

void DevicesModel::addDeviceInfo(const QBluetoothDeviceInfo& info)
{
    if (!m_deviceInfos.contains(info)) {
        int row = m_deviceInfos.count();

        this->beginInsertRows(QModelIndex(), row, row);
        m_deviceInfos.append(info);
        this->endInsertRows();
    }
}

void DevicesModel::removeDeviceInfo(const QBluetoothDeviceInfo& info)
{
    if (m_deviceInfos.contains(info)) {
        int row = m_deviceInfos.indexOf(info);

        this->beginRemoveRows(QModelIndex(), row, row);
        m_deviceInfos.removeAt(row);
        this->endRemoveRows();
    }
}

void DevicesModel::clearDeviceInfos()
{
    this->beginResetModel();
    m_deviceInfos.clear();
    this->endResetModel();
}
