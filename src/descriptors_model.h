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

#ifndef DESCRIPTORS_MODEL_H_
#define DESCRIPTORS_MODEL_H_

#include <QtBluetooth/QLowEnergyDescriptor>
#include <QtCore/QAbstractListModel>

class DescriptorsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        Name = Qt::UserRole + 1,
        Uuid = Qt::UserRole + 2,
        HasValue = Qt::UserRole + 3,
        Value = Qt::UserRole + 4,
    };
    Q_ENUM(Roles);

    explicit DescriptorsModel(QObject* parent = nullptr);

    DescriptorsModel(const DescriptorsModel&) = delete;
    DescriptorsModel(DescriptorsModel&&) = delete;

    DescriptorsModel& operator = (const DescriptorsModel&) = delete;
    DescriptorsModel& operator = (DescriptorsModel&&) = delete;

    ~DescriptorsModel() override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QList<QLowEnergyDescriptor> descriptors() const;
    QLowEnergyDescriptor descriptor(int index) const;

    void setDescriptors(const QList<QLowEnergyDescriptor>& descriptors);

    void addDescriptor(const QLowEnergyDescriptor& descriptor);
    void removeDescriptor(const QLowEnergyDescriptor& descriptor);
    void updateDescriptor(const QLowEnergyDescriptor& descriptor);

    void clearDescriptors();

private:
    QList<QLowEnergyDescriptor> m_descriptors;
};

#endif  // DESCRIPTORS_MODEL_H_
