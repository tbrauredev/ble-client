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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "globals.h"

#include <QtBluetooth/QBluetoothUuid>
#include <QtCore/QObject>

class Settings : public QObject
{
    Q_OBJECT

public:
    Settings(const Settings&) = delete;
    Settings(Settings&&) = delete;

    Settings& operator = (const Settings&) = delete;
    Settings& operator = (Settings&&) = delete;

    ~Settings() override;

    Q_INVOKABLE int logMaximumLength() const;
    Q_INVOKABLE void setLogMaximumLength(int count);

    Q_INVOKABLE Globals::LogFormat logExportFormat() const;
    Q_INVOKABLE void setLogExportFormat(Globals::LogFormat format);

    Q_INVOKABLE Globals::DisplayMode characteristicDisplayMode(
        const QBluetoothUuid& uuid) const;

    Q_INVOKABLE Globals::DisplayMode characteristicDisplayMode(
        const QString& uuid) const;

    Q_INVOKABLE void setCharacteristicDisplayMode(
        const QBluetoothUuid& uuid,
        Globals::DisplayMode mode);

    Q_INVOKABLE void setCharacteristicDisplayMode(
        const QString& uuid,
        Globals::DisplayMode mode);

    Q_INVOKABLE Globals::DisplayMode descriptorDisplayMode(
        const QBluetoothUuid& uuid) const;

    Q_INVOKABLE Globals::DisplayMode descriptorDisplayMode(
        const QString& uuid) const;

    Q_INVOKABLE void setDescriptorDisplayMode(
        const QBluetoothUuid& uuid,
        Globals::DisplayMode mode);

    Q_INVOKABLE void setDescriptorDisplayMode(
        const QString& uuid,
        Globals::DisplayMode mode);

    Q_SIGNAL void settingsChanged();

    static Settings* instance();

private:
    explicit Settings();
};

#endif    // SETTINGS_H_
