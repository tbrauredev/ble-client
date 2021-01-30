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

#include "settings.h"

#include <QtCore/QSettings>

static QString kLogMaximumLength = "log-maximum-length";
static QString kLogExportFormat = "log-export-format";
static QString kCharacteristicPrefix = "characteristic-";
static QString kDescriptorPrefix = "descriptor-";
static QString kDisplayModeSuffix = "-display-mode";

Settings::~Settings() {}

int Settings::logMaximumLength() const
{
    return QSettings().value(kLogMaximumLength, 4096).toInt();
}

void Settings::setLogMaximumLength(int count)
{
    QSettings().setValue(kLogMaximumLength, count);
    Q_EMIT settingsChanged();
}

Globals::LogFormat Settings::logExportFormat() const
{
    return static_cast<Globals::LogFormat>(
        QSettings().value(
            kLogExportFormat,
            static_cast<int>(Globals::LogFormat::Csv)).toInt());
}

void Settings::setLogExportFormat(Globals::LogFormat format)
{
    QSettings().setValue(kLogExportFormat, static_cast<int>(format));
    Q_EMIT settingsChanged();
}

Globals::DisplayMode Settings::characteristicDisplayMode(
    const QBluetoothUuid& uuid) const
{
    return this->characteristicDisplayMode(uuid.toString(QUuid::WithoutBraces));
}

Globals::DisplayMode Settings::characteristicDisplayMode(
    const QString& uuid) const
{
    return static_cast<Globals::DisplayMode>(
        QSettings().value(
            kCharacteristicPrefix + uuid + kDisplayModeSuffix,
            static_cast<int>(Globals::DisplayMode::Hexadecimal)).toInt());
}

void Settings::setCharacteristicDisplayMode(
    const QBluetoothUuid& uuid,
    Globals::DisplayMode mode)
{
    this->setCharacteristicDisplayMode(uuid.toString(QUuid::WithoutBraces), mode);
}

void Settings::setCharacteristicDisplayMode(
    const QString& uuid,
    Globals::DisplayMode mode)
{
    QSettings().setValue(
        kCharacteristicPrefix + uuid + kDisplayModeSuffix,
        static_cast<int>(mode));

    Q_EMIT settingsChanged();
}

Globals::DisplayMode Settings::descriptorDisplayMode(
    const QBluetoothUuid& uuid) const
{
    return this->descriptorDisplayMode(uuid.toString(QUuid::WithoutBraces));
}

Globals::DisplayMode Settings::descriptorDisplayMode(
    const QString& uuid) const
{
    return static_cast<Globals::DisplayMode>(
        QSettings().value(
            kDescriptorPrefix + uuid + kDisplayModeSuffix,
            static_cast<int>(Globals::DisplayMode::Hexadecimal)).toInt());
}

void Settings::setDescriptorDisplayMode(
    const QBluetoothUuid& uuid,
    Globals::DisplayMode mode)
{
    this->setDescriptorDisplayMode(uuid.toString(QUuid::WithoutBraces), mode);
}

void Settings::setDescriptorDisplayMode(
    const QString& uuid,
    Globals::DisplayMode mode)
{
    QSettings().setValue(
        kDescriptorPrefix + uuid + kDisplayModeSuffix,
        static_cast<int>(mode));

    Q_EMIT settingsChanged();
}

Settings* Settings::instance()
{
    static Settings instance;
    return &instance;
}

Settings::Settings()
{
    QSettings::setDefaultFormat(QSettings::IniFormat);
}
