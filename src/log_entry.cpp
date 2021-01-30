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

#include "log_entry.h"
#include "log_entry_p.h"

//==============================================================================
// LogEntry
//==============================================================================
LogEntry::LogEntry(Event event) :
    m_d(new LogEntryPrivate())
{
    m_d->m_dateTime = QDateTime::currentDateTime();
    m_d->m_event = event;
}

LogEntry::LogEntry(const LogEntry& other)
{
    m_d = other.m_d;
}

LogEntry::LogEntry(LogEntry&& other)
{
    m_d = other.m_d;
}

LogEntry& LogEntry::operator = (const LogEntry& rhs)
{
    m_d = rhs.m_d;
    return *this;
}

LogEntry& LogEntry::operator = (LogEntry&& rhs)
{
    m_d = rhs.m_d;
    return *this;
}

LogEntry::~LogEntry() {}

QDateTime LogEntry::dateTime() const
{
    return m_d->m_dateTime;
}

LogEntry::Event LogEntry::event() const
{
    return m_d->m_event;
}

QBluetoothAddress LogEntry::deviceAddress() const
{
    return m_d->m_deviceAddress;
}

void LogEntry::setDeviceAddress(const QBluetoothAddress& address)
{
    m_d->m_deviceAddress = address;
}

QString LogEntry::deviceName() const
{
    return m_d->m_deviceName;
}

void LogEntry::setDeviceName(const QString& name)
{
    m_d->m_deviceName = name;
}

QBluetoothUuid LogEntry::serviceUuid() const
{
    return m_d->m_serviceUuid;
}

void LogEntry::setServiceUuid(const QBluetoothUuid& uuid)
{
    m_d->m_serviceUuid = uuid;
}

QBluetoothUuid LogEntry::characteristicUuid() const
{
    return m_d->m_characteristicUuid;
}

void LogEntry::setCharacteristicUuid(const QBluetoothUuid& uuid)
{
    m_d->m_characteristicUuid = uuid;
}

QBluetoothUuid LogEntry::descriptorUuid() const
{
    return m_d->m_descriptorUuid;
}

void LogEntry::setDescriptorUuid(const QBluetoothUuid& uuid)
{
    m_d->m_descriptorUuid = uuid;
}

QByteArray LogEntry::value() const
{
    return m_d->m_value;
}

void LogEntry::setValue(const QByteArray& value)
{
    m_d->m_value = value;
}

QString LogEntry::errorMessage() const
{
    return m_d->m_errorMessage;
}

void LogEntry::setErrorMessage(const QString& message)
{
    m_d->m_errorMessage = message;
}

//==============================================================================
// LogEntryPrivate
//==============================================================================
LogEntryPrivate::LogEntryPrivate() {}
