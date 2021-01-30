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

#include "logger_model.h"
#include "globals.h"
#include "settings.h"

LoggerModel::LoggerModel(Logger* logger, QObject* parent) :
    QAbstractListModel(parent),
    m_logger(logger)
{
    Q_ASSERT(logger != nullptr);

    QObject::connect(
        m_logger,
        &Logger::entriesAboutToChange,
        this,
        &LoggerModel::handleEntriesAboutToChange);

    QObject::connect(
        m_logger,
        &Logger::entriesChanged,
        this,
        &LoggerModel::handleEntriesChanged);

    QObject::connect(
        m_logger,
        &Logger::entryAboutToBeAdded,
        this,
        &LoggerModel::handleEntryAboutToBeAdded);

    QObject::connect(
        m_logger,
        &Logger::entryAdded,
        this,
        &LoggerModel::handleEntryAdded);

    QObject::connect(
        m_logger,
        &Logger::entryAboutToBeRemoved,
        this,
        &LoggerModel::handleEntryAboutToBeRemoved);

    QObject::connect(
        m_logger,
        &Logger::entryRemoved,
        this,
        &LoggerModel::handleEntryRemoved);
}

LoggerModel::~LoggerModel() {}

int LoggerModel::rowCount(const QModelIndex& parent) const
{
    if (m_logger != nullptr)
        return m_logger->entries().count();
    else
        return 0;
}

QVariant LoggerModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= m_logger->entries().count())
        return QVariant();

    LogEntry entry = m_logger->entries()[index.row()];
    switch (static_cast<Roles>(role)) {
        case Roles::DateTime:
            return entry.dateTime().toString();

        case Roles::Event:
            return static_cast<int>(entry.event());

        case Roles::HasDevice:
            return !entry.deviceAddress().isNull();

        case Roles::DeviceAddress:
            return entry.deviceAddress().toString();

        case Roles::DeviceName:
            return entry.deviceName();

        case Roles::HasService:
            return !entry.serviceUuid().isNull();

        case Roles::ServiceUuid:
            return entry.serviceUuid().toString(QUuid::WithoutBraces);

        case Roles::ServiceName:
            return Globals::instance()->serviceName(entry.serviceUuid());

        case Roles::HasCharacteristic:
            return !entry.characteristicUuid().isNull();

        case Roles::CharacteristicUuid:
            return entry.characteristicUuid().toString(QUuid::WithoutBraces);

        case Roles::CharacteristicName:
            return Globals::instance()->characteristicName(entry.characteristicUuid());

        case Roles::HasDescriptor:
            return !entry.descriptorUuid().isNull();

        case Roles::DescriptorUuid:
            return entry.descriptorUuid().toString(QUuid::WithoutBraces);

        case Roles::DescriptorName:
            return Globals::instance()->descriptorName(entry.descriptorUuid());

        case Roles::HasValue:
            return !entry.value().isEmpty();

        case Roles::Value:
            return entry.value();

        case Roles::ErrorMessage:
            return entry.errorMessage();

        case Roles::Message:
            return this->entryMessage(entry);

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> LoggerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::DateTime)] = "dateTime";
    roles[static_cast<int>(Roles::Event)] = "event";
    roles[static_cast<int>(Roles::HasDevice)] = "hasDevice";
    roles[static_cast<int>(Roles::DeviceAddress)] = "deviceAddress";
    roles[static_cast<int>(Roles::DeviceName)] = "deviceName";
    roles[static_cast<int>(Roles::HasService)] = "hasService";
    roles[static_cast<int>(Roles::ServiceUuid)] = "serviceUuid";
    roles[static_cast<int>(Roles::ServiceName)] = "serviceName";
    roles[static_cast<int>(Roles::HasCharacteristic)] = "hasCharacteristic";
    roles[static_cast<int>(Roles::CharacteristicUuid)] = "characteristicUuid";
    roles[static_cast<int>(Roles::CharacteristicName)] = "characteristicName";
    roles[static_cast<int>(Roles::HasDescriptor)] = "hasDescriptor";
    roles[static_cast<int>(Roles::DescriptorUuid)] = "descriptorUuid";
    roles[static_cast<int>(Roles::DescriptorName)] = "descriptorName";
    roles[static_cast<int>(Roles::HasValue)] = "hasValue";
    roles[static_cast<int>(Roles::Value)] = "value";
    roles[static_cast<int>(Roles::ErrorMessage)] = "errorMessage";
    roles[static_cast<int>(Roles::Message)] = "message";
    return roles;
}

Logger* LoggerModel::logger() const
{
    return m_logger;
}

void LoggerModel::handleEntriesAboutToChange()
{
    this->beginResetModel();
}

void LoggerModel::handleEntriesChanged()
{
    this->endResetModel();
}

void LoggerModel::handleEntryAboutToBeAdded()
{
    int row = m_logger->entries().count();
    this->beginInsertRows(QModelIndex(), row, row);
}

void LoggerModel::handleEntryAdded()
{
    this->endInsertRows();
}

void LoggerModel::handleEntryAboutToBeRemoved()
{
    this->beginRemoveRows(QModelIndex(), 0, 0);
}

void LoggerModel::handleEntryRemoved()
{
    this->endRemoveRows();
}

QString LoggerModel::entryMessage(const LogEntry& entry) const
{
    switch (entry.event()) {
        case LogEntry::Event::DeviceDiscoveryStarted:
            return tr("Device discovery started");

        case LogEntry::Event::DeviceDiscovered:
            return tr("Device [%1] discovered")
                .arg(entry.deviceAddress().toString());

        case LogEntry::Event::DeviceDiscoveryStopped:
            return tr("Device discovery stopped");

        case LogEntry::Event::DeviceConnected:
            return tr("Connected to device [%1]")
                .arg(entry.deviceAddress().toString());

        case LogEntry::Event::DeviceDisconnected:
            return tr("Disconnected from device [%1]")
                .arg(entry.deviceAddress().toString());

        case LogEntry::Event::ServiceDiscoveryStarted:
            return tr("Starting service discovery of device [%1]")
                .arg(entry.deviceAddress().toString());

        case LogEntry::Event::ServiceDiscovered:
            return tr("Service [%2] of device [%1] discovered")
                .arg(entry.deviceAddress().toString())
                .arg(entry.serviceUuid().toString(QUuid::WithoutBraces));

        case LogEntry::Event::ServiceDiscoveryFinished:
            return tr("Service discovery of device [%1] finished")
                .arg(entry.deviceAddress().toString());

        case LogEntry::Event::ServiceDetailsDiscoveryStarted:
            return tr("Starting details discovery of service [%1]")
                .arg(entry.serviceUuid().toString(QUuid::WithoutBraces));

        case LogEntry::Event::ServiceDetailsDiscoveryFinished:
            return tr("Details discovery of service [%1] finished")
                .arg(entry.serviceUuid().toString(QUuid::WithoutBraces));

        case LogEntry::Event::WrittingCharacteristic:
            return tr("Writting characteristic [%1], value: [%2]")
                .arg(entry.characteristicUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->characteristicDisplayMode(entry.characteristicUuid())));

        case LogEntry::Event::CharacteristicChanged:
            return tr("Characteristic [%1] changed, value: [%2]")
                .arg(entry.characteristicUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->characteristicDisplayMode(entry.characteristicUuid())));

        case LogEntry::Event::CharacteristicRead:
            return tr("Characteristic [%1] read, value: [%2]")
                .arg(entry.characteristicUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->characteristicDisplayMode(entry.characteristicUuid())));

        case LogEntry::Event::CharacteristicWritten:
            return tr("Characteristic [%1] written, value: [%2]")
                .arg(entry.characteristicUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->characteristicDisplayMode(entry.characteristicUuid())));

        case LogEntry::Event::WrittingDescriptor:
            return tr("Writting descriptor [%1], value: [%2]")
                .arg(entry.descriptorUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->descriptorDisplayMode(entry.descriptorUuid())));

        case LogEntry::Event::DescriptorRead:
            return tr("Descriptor [%1] read, value: [%2]")
                .arg(entry.descriptorUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->descriptorDisplayMode(entry.descriptorUuid())));

        case LogEntry::Event::DescriptorWritten:
            return tr("Descriptor [%1] written, value: [%2]")
                .arg(entry.descriptorUuid().toString(QUuid::WithoutBraces))
                .arg(Globals::instance()->valueToString(
                    entry.value(),
                    Settings::instance()->descriptorDisplayMode(entry.descriptorUuid())));

        case LogEntry::Event::ErrorOccurred:
            return tr("Error occurred: %2")
                .arg(entry.errorMessage());

        default:
            return QString();
    }
}
