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

#ifndef LOG_ENTRY_H_
#define LOG_ENTRY_H_

#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothUuid>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QDateTime>
#include <QtCore/QString>

class LogEntryPrivate;

class LogEntry
{
    Q_GADGET

public:
    enum class Event {
        DeviceDiscoveryStarted,
        DeviceDiscovered,
        DeviceDiscoveryStopped,
        DeviceConnected,
        DeviceDisconnected,
        ServiceDiscoveryStarted,
        ServiceDiscovered,
        ServiceDiscoveryFinished,
        ServiceDetailsDiscoveryStarted,
        ServiceDetailsDiscoveryFinished,
        WrittingCharacteristic,
        CharacteristicChanged,
        CharacteristicRead,
        CharacteristicWritten,
        WrittingDescriptor,
        DescriptorRead,
        DescriptorWritten,
        ErrorOccurred,
    };
    Q_ENUM(Event);

    explicit LogEntry(Event event);

    LogEntry(const LogEntry& other);
    LogEntry(LogEntry&& other);

    LogEntry& operator = (const LogEntry& rhs);
    LogEntry& operator = (LogEntry&& rhs);

    ~LogEntry();

    QDateTime dateTime() const;
    Event event() const;

    QBluetoothAddress deviceAddress() const;
    void setDeviceAddress(const QBluetoothAddress& address);

    QString deviceName() const;
    void setDeviceName(const QString& name);

    QBluetoothUuid serviceUuid() const;
    void setServiceUuid(const QBluetoothUuid& uuid);

    QBluetoothUuid characteristicUuid() const;
    void setCharacteristicUuid(const QBluetoothUuid& uuid);

    QBluetoothUuid descriptorUuid() const;
    void setDescriptorUuid(const QBluetoothUuid& uuid);

    QByteArray value() const;
    void setValue(const QByteArray& value);

    QString errorMessage() const;
    void setErrorMessage(const QString& message);

private:
    QSharedDataPointer<LogEntryPrivate> m_d;
};

#endif  // LOG_ENTRY_H_
