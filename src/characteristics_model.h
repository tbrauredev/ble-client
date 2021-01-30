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

#ifndef CHARACTERISTICS_MODEL_H_
#define CHARACTERISTICS_MODEL_H_

#include <QtBluetooth/QLowEnergyCharacteristic>
#include <QtCore/QAbstractListModel>

class CharacteristicsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        Name = Qt::UserRole + 1,
        Uuid = Qt::UserRole + 2,
        Properties = Qt::UserRole + 3,
        HasValue = Qt::UserRole + 4,
        Value = Qt::UserRole + 5,
    };
    Q_ENUM(Roles);

    explicit CharacteristicsModel(QObject* parent = nullptr);

    CharacteristicsModel(const CharacteristicsModel&) = delete;
    CharacteristicsModel(CharacteristicsModel&&) = delete;

    CharacteristicsModel& operator = (const CharacteristicsModel&) = delete;
    CharacteristicsModel& operator = (CharacteristicsModel&&) = delete;

    ~CharacteristicsModel() override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QList<QLowEnergyCharacteristic> characteristics() const;
    QLowEnergyCharacteristic characteristic(int index) const;

    void setCharacteristics(
        const QList<QLowEnergyCharacteristic>& characteristics);

    void addCharacteristic(const QLowEnergyCharacteristic& characteristic);
    void removeCharacteristic(const QLowEnergyCharacteristic& characteristic);
    void updateCharacteristic(const QLowEnergyCharacteristic& characteristic);

    void clearCharacteristics();

private:
    QList<QLowEnergyCharacteristic> m_characteristics;
};

#endif  // CHARACTERISTICS_MODEL_H_
