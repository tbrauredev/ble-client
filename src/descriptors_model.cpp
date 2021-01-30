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

#include "descriptors_model.h"
#include "globals.h"
#include "settings.h"

DescriptorsModel::DescriptorsModel(QObject* parent) :
    QAbstractListModel(parent) {}

DescriptorsModel::~DescriptorsModel() {}

int DescriptorsModel::rowCount(const QModelIndex& parent) const
{
    return m_descriptors.count();
}

QVariant DescriptorsModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= m_descriptors.count())
        return QVariant();

    QLowEnergyDescriptor descriptor = m_descriptors[index.row()];
    switch (static_cast<Roles>(role)) {
        case Roles::Name:
            return Globals::instance()->descriptorName(descriptor.uuid());

        case Roles::Uuid:
            return descriptor.uuid().toString(QUuid::WithoutBraces);

        case Roles::HasValue:
            return !descriptor.value().isEmpty();

        case Roles::Value:
            return descriptor.value();

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> DescriptorsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::Name)] = "name";
    roles[static_cast<int>(Roles::Uuid)] = "uuid";
    roles[static_cast<int>(Roles::HasValue)] = "hasValue";
    roles[static_cast<int>(Roles::Value)] = "value";
    return roles;
}

QList<QLowEnergyDescriptor> DescriptorsModel::descriptors() const
{
    return m_descriptors;
}

QLowEnergyDescriptor DescriptorsModel::descriptor(int index) const
{
    if (index < m_descriptors.count())
        return m_descriptors[index];
    else
        return QLowEnergyDescriptor();
}

void DescriptorsModel::setDescriptors(
    const QList<QLowEnergyDescriptor>& descriptors)
{
    this->beginResetModel();
    m_descriptors = descriptors;
    this->endResetModel();
}

void DescriptorsModel::addDescriptor(const QLowEnergyDescriptor& descriptor)
{
    if (!m_descriptors.contains(descriptor)) {
        int row = m_descriptors.count();

        this->beginInsertRows(QModelIndex(), row, row);
        m_descriptors.append(descriptor);
        this->endInsertRows();
    }
}

void DescriptorsModel::removeDescriptor(const QLowEnergyDescriptor& descriptor)
{
    if (m_descriptors.contains(descriptor)) {
        int row = m_descriptors.indexOf(descriptor);

        this->beginRemoveRows(QModelIndex(), row, row);
        m_descriptors.removeAt(row);
        this->endRemoveRows();
    }
}

void DescriptorsModel::updateDescriptor(const QLowEnergyDescriptor& descriptor)
{
    Q_ASSERT(m_descriptors.contains(descriptor));

    int row = m_descriptors.indexOf(descriptor);
    QModelIndex index = this->createIndex(row, 0);

    Q_EMIT dataChanged(index, index, {Roles::Value});
}

void DescriptorsModel::clearDescriptors()
{
    this->beginResetModel();
    m_descriptors.clear();
    this->endResetModel();
}
