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

#include "characteristics_model.h"
#include "globals.h"
#include "settings.h"

CharacteristicsModel::CharacteristicsModel(QObject* parent) :
    QAbstractListModel(parent) {}

CharacteristicsModel::~CharacteristicsModel() {}

int CharacteristicsModel::rowCount(const QModelIndex& parent) const
{
    return m_characteristics.count();
}

QVariant CharacteristicsModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= m_characteristics.count())
        return QVariant();

    QLowEnergyCharacteristic characteristic = m_characteristics[index.row()];
    switch (static_cast<Roles>(role)) {
        case Roles::Name:
            return Globals::instance()->characteristicName(characteristic.uuid());

        case Roles::Uuid:
            return characteristic.uuid().toString(QUuid::WithoutBraces);

        case Roles::Properties:
            return characteristic.properties().toInt();

        case Roles::HasValue:
            return !characteristic.value().isEmpty();

        case Roles::Value:
            return characteristic.value();

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> CharacteristicsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::Name)] = "name";
    roles[static_cast<int>(Roles::Uuid)] = "uuid";
    roles[static_cast<int>(Roles::Properties)] = "properties";
    roles[static_cast<int>(Roles::HasValue)] = "hasValue";
    roles[static_cast<int>(Roles::Value)] = "value";
    return roles;
}

QList<QLowEnergyCharacteristic> CharacteristicsModel::characteristics() const
{
    return m_characteristics;
}

QLowEnergyCharacteristic CharacteristicsModel::characteristic(int index) const
{
    if (index < m_characteristics.count())
        return m_characteristics[index];
    else
        return QLowEnergyCharacteristic();
}

void CharacteristicsModel::setCharacteristics(
    const QList<QLowEnergyCharacteristic>& characteristics)
{
    this->beginResetModel();
    m_characteristics = characteristics;
    this->endResetModel();
}

void CharacteristicsModel::addCharacteristic(
    const QLowEnergyCharacteristic& characteristic)
{
    if (!m_characteristics.contains(characteristic)) {
        int row = m_characteristics.count();

        this->beginInsertRows(QModelIndex(), row, row);
        m_characteristics.append(characteristic);
        this->endInsertRows();
    }
}

void CharacteristicsModel::removeCharacteristic(
    const QLowEnergyCharacteristic& characteristic)
{
    if (m_characteristics.contains(characteristic)) {
        int row = m_characteristics.indexOf(characteristic);

        this->beginRemoveRows(QModelIndex(), row, row);
        m_characteristics.removeAt(row);
        this->endRemoveRows();
    }
}

void CharacteristicsModel::updateCharacteristic(
    const QLowEnergyCharacteristic& characteristic)
{
    Q_ASSERT(m_characteristics.contains(characteristic));

    int row = m_characteristics.indexOf(characteristic);
    QModelIndex index = this->createIndex(row, 0);

    Q_EMIT dataChanged(index, index, {Roles::Value});
}

void CharacteristicsModel::clearCharacteristics()
{
    this->beginResetModel();
    m_characteristics.clear();
    this->endResetModel();
}
