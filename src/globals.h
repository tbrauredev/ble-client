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

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <QtBluetooth/QLowEnergyCharacteristic>
#include <QtBluetooth/QBluetoothUuid>
#include <QtCore/QObject>

class Globals : public QObject
{
    Q_OBJECT

public:
    enum class DisplayMode {
        Hexadecimal,
        Text,
        Binary,
    };
    Q_ENUM(DisplayMode);

    enum class LogFormat {
        Csv,
        Json,
    };
    Q_ENUM(LogFormat);

    enum class CharacteristicProperties {
        Unknown = QLowEnergyCharacteristic::Unknown,
        Broadcasting = QLowEnergyCharacteristic::Broadcasting,
        Read = QLowEnergyCharacteristic::Read,
        Write = QLowEnergyCharacteristic::Write,
        WriteNoResponse = QLowEnergyCharacteristic::WriteNoResponse,
        WriteSigned = QLowEnergyCharacteristic::WriteSigned,
        Notify = QLowEnergyCharacteristic::Notify,
        Indicate = QLowEnergyCharacteristic::Indicate,
    };
    Q_ENUM(CharacteristicProperties);

    Globals(const Globals&) = delete;
    Globals(Globals&&) = delete;

    Globals& operator = (const Globals&) = delete;
    Globals& operator = (Globals&&) = delete;

    ~Globals() override;

    Q_INVOKABLE QString valueToString(const QByteArray& value, DisplayMode mode) const;
    Q_INVOKABLE QByteArray valueFromString(const QString& value, DisplayMode mode) const;

    Q_INVOKABLE QString serviceName(const QBluetoothUuid& uuid) const;
    Q_INVOKABLE QString characteristicName(const QBluetoothUuid& uuid) const;
    Q_INVOKABLE QString descriptorName(const QBluetoothUuid& uuid) const;

    static Globals* instance();

private:
    explicit Globals();
};

#endif  // GLOBALS_H_
