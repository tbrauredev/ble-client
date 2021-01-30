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

#ifndef QML_TYPES_H_
#define QML_TYPES_H_

#include "bluetooth_controller.h"
#include "globals.h"
#include "logger.h"
#include "settings.h"

#include <QtQml>

static inline void registerQmlTypes()
{
    qmlRegisterUncreatableType<BluetoothController>(
        "BluetoothController",
        1,
        0,
        "BluetoothController",
        "BluetoothController Type");

    qmlRegisterUncreatableType<Globals>(
        "Globals",
        1,
        0,
        "Globals",
        "Globals Type");

    qmlRegisterUncreatableType<Logger>(
        "Logger",
        1,
        0,
        "Logger",
        "Logger Type");

    qmlRegisterUncreatableType<Settings>(
        "Settings",
        1,
        0,
        "Settings",
        "Settings Type");
}

#endif    // QML_TYPES_H_
