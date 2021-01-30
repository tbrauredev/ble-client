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

#ifndef LOGGER_MODEL_H_
#define LOGGER_MODEL_H_

#include "logger.h"

#include <QtCore/QAbstractListModel>

class LoggerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum class Roles {
        DateTime = Qt::UserRole + 1,
        Event = Qt::UserRole + 2,
        HasDevice = Qt::UserRole + 3,
        DeviceAddress = Qt::UserRole + 4,
        DeviceName = Qt::UserRole + 5,
        HasService = Qt::UserRole + 6,
        ServiceUuid = Qt::UserRole + 7,
        ServiceName = Qt::UserRole + 8,
        HasCharacteristic = Qt::UserRole + 9,
        CharacteristicUuid = Qt::UserRole + 10,
        CharacteristicName = Qt::UserRole + 11,
        HasDescriptor = Qt::UserRole + 12,
        DescriptorUuid = Qt::UserRole + 13,
        DescriptorName = Qt::UserRole + 14,
        HasValue = Qt::UserRole + 15,
        Value = Qt::UserRole + 16,
        ErrorMessage = Qt::UserRole + 17,
        Message = Qt::UserRole + 18,
    };
    Q_ENUM(Roles);

    explicit LoggerModel(Logger* logger, QObject* parent = nullptr);

    LoggerModel(const LoggerModel&) = delete;
    LoggerModel(LoggerModel&&) = delete;

    LoggerModel& operator = (const LoggerModel&) = delete;
    LoggerModel& operator = (LoggerModel&&) = delete;

    ~LoggerModel() override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    Logger* logger() const;

private:
    Q_SLOT void handleEntriesAboutToChange();
    Q_SLOT void handleEntriesChanged();
    Q_SLOT void handleEntryAboutToBeAdded();
    Q_SLOT void handleEntryAdded();
    Q_SLOT void handleEntryAboutToBeRemoved();
    Q_SLOT void handleEntryRemoved();

    QString entryMessage(const LogEntry& entry) const;

    Logger* m_logger;
};

#endif    // LOGGER_MODEL_H_
