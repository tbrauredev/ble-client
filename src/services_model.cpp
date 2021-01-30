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

#include "services_model.h"
#include "globals.h"

ServicesModel::ServicesModel(QObject* parent) :
    QAbstractListModel(parent) {}

ServicesModel::~ServicesModel() {}

int ServicesModel::rowCount(const QModelIndex& parent) const
{
    return m_serviceUuids.count();
}

QVariant ServicesModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= m_serviceUuids.count())
        return QVariant();

    QBluetoothUuid uuid = m_serviceUuids[index.row()];
    switch (static_cast<Roles>(role)) {
        case Roles::Name:
            return Globals::instance()->serviceName(uuid);

        case Roles::Uuid:
            return uuid.toString(QUuid::WithoutBraces);

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ServicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::Name)] = "name";
    roles[static_cast<int>(Roles::Uuid)] = "uuid";
    return roles;
}

QList<QBluetoothUuid> ServicesModel::serviceUuids() const
{
    return m_serviceUuids;
}

QBluetoothUuid ServicesModel::serviceUuid(int index) const
{
    if (index < m_serviceUuids.count())
        return m_serviceUuids[index];
    else
        return QBluetoothUuid();
}

void ServicesModel::addServiceUuid(const QBluetoothUuid& uuid)
{
    if (!m_serviceUuids.contains(uuid)) {
        int row = m_serviceUuids.count();

        this->beginInsertRows(QModelIndex(), row, row);
        m_serviceUuids.append(uuid);
        this->endInsertRows();
    }
}

void ServicesModel::removeServiceUuid(const QBluetoothUuid& uuid)
{
    if (m_serviceUuids.contains(uuid)) {
        int row = m_serviceUuids.indexOf(uuid);

        this->beginRemoveRows(QModelIndex(), row, row);
        m_serviceUuids.removeAt(row);
        this->endRemoveRows();
    }
}

void ServicesModel::clearServiceUuids()
{
    this->beginResetModel();
    m_serviceUuids.clear();
    this->endResetModel();
}
