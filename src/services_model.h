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

#ifndef SERVICES_MODEL_H_
#define SERVICES_MODEL_H_

#include <QtBluetooth/QBluetoothUuid>
#include <QtCore/QAbstractListModel>

class ServicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        Name = Qt::UserRole + 1,
        Uuid = Qt::UserRole + 2,
    };
    Q_ENUM(Roles);

    explicit ServicesModel(QObject* parent = nullptr);

    ServicesModel(const ServicesModel&) = delete;
    ServicesModel(ServicesModel&&) = delete;

    ServicesModel& operator = (const ServicesModel&) = delete;
    ServicesModel& operator = (ServicesModel&&) = delete;

    ~ServicesModel() override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QList<QBluetoothUuid> serviceUuids() const;
    QBluetoothUuid serviceUuid(int index) const;

    void addServiceUuid(const QBluetoothUuid& uuid);
    void removeServiceUuid(const QBluetoothUuid& uuid);

    void clearServiceUuids();

private:
    QList<QBluetoothUuid> m_serviceUuids;
};

#endif    // SERVICES_MODEL_H_
